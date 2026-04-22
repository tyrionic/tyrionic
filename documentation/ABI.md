# Tyrion C ABI Extensions

This document explains how to extend Tyrion with C extensions in `extensions/` and compile them into produced binaries.

## Overview

Tyrion supports a static host-extension ABI (`tyrion-host-ext/v1`).
Each extension exports one C entrypoint (`call_symbol`) and can be called from Tyrion via:

- `__tyrion_native_host_load(name_or_path)`
- `__tyrion_native_host_call(handle, op, payload)`
- `__tyrion_native_host_unload(handle)`

In normal project usage, you wrap these low-level calls in `wrapper.ty` helper functions.

## Extension Directory Layout

```text
extensions/
  <extension-name>/
    ext.toml
    src/
      *.c
    wrapper.ty        # optional but recommended
```

Default discovery directory is `./extensions`.

## `ext.toml` Schema

Required keys:

- `name = "foobar"`
- `abi = "tyrion-host-ext/v1"`
- `call_symbol = "tyext_foobar_call_v1"`
- `sources = ["src/foobar.c"]`

Optional keys:

- `include_dirs = ["include"]`
- `cflags = ["-DMY_FLAG=1"]`
- `host_call_eval_default = "literal" | "runtime"` (default: `literal`)
- `host_call_eval_runtime_ops = ["ext.op"]`
- `host_call_eval_literal_ops = ["ext.other"]`

Validation rules:

- `name` may contain only `[A-Za-z0-9_-]`
- `call_symbol` may contain only `[A-Za-z0-9_]`
- `sources` and `include_dirs` must be relative paths
- `sources`/`include_dirs` cannot contain `..`

## C Entrypoint Contract

Your extension must export:

```c
const char* tyext_foobar_call_v1(const char* op, const char* payload);
```

Behavior:

- `op` identifies the operation (for example: `"foobar.randomcase"`).
- `payload` is a UTF-8 string argument.
- Return UTF-8 text for success.
- Return `NULL` when the operation is unavailable or has no value.

Compatibility note:

- For dynamic host-shim compatibility, `"<none>"` and `"__TYEXT_NONE__"` are also treated as no-value by host gateways.
- For strict static behavior, returning `NULL` is the clearest no-value signal.

## Minimal Example

`extensions/foobar/ext.toml`:

```toml
name = "foobar"
abi = "tyrion-host-ext/v1"
call_symbol = "tyext_foobar_call_v1"
sources = ["src/foobar.c"]
host_call_eval_default = "literal"
host_call_eval_runtime_ops = ["foobar.randomcase"]
```

`extensions/foobar/src/foobar.c`:

```c
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

const char* tyext_foobar_call_v1(const char* op, const char* payload) {
  static char out[4096];
  if (!op || !payload) return NULL;
  if (strcmp(op, "foobar.randomcase") != 0 && strcmp(op, "foobar") != 0) return NULL;
  size_t n = strlen(payload);
  if (n >= sizeof(out)) n = sizeof(out) - 1;
  for (size_t i = 0; i < n; i++) {
    unsigned char c = (unsigned char)payload[i];
    out[i] = (rand() & 1) ? (char)toupper(c) : (char)tolower(c);
  }
  out[n] = '\0';
  return out;
}
```

`extensions/foobar/wrapper.ty`:

```python
_foobar_handle = none

def _foobar_handle_get():
    global _foobar_handle
    if _foobar_handle == none:
        _foobar_handle = __tyrion_native_host_load("foobar")
    return _foobar_handle

def foobar(text):
    out = __tyrion_native_host_call(_foobar_handle_get(), "foobar.randomcase", text)
    if out == none:
        raise "foobar.randomcase operation unavailable"
    return out
```

## Build with Extensions

Compile with strict extension requirement:

```bash
./tyrionc --backend=tyrionc --ext-static=required --ext-dir ./extensions --build app.ty --out app
```

Auto mode (default on strict compiler builds):

```bash
./tyrionc --backend=tyrionc --ext-static=auto --build app.ty --out app
```

## Wrapper Injection (`--with-stdlib`)

You can prepend a wrapper source file during build:

```bash
./tyrionc --backend=tyrionc --ext-static=required --with-stdlib=./extensions/foobar/wrapper.ty --build app.ty --out app
```

If `--with-stdlib` is omitted, compiler wrapper auto-discovery applies from:

- `extensions/*/wrapper.ty`

## Runtime-vs-Literal Host Call Policy

`host_call_eval_*` controls when host calls are folded at compile time vs executed at runtime:

- `literal`: compiler may fold call results when safe.
- `runtime`: call is kept for runtime execution in the produced binary.

Use runtime mode for non-deterministic operations (`random`, clock-based behavior, external state).

## Failure Modes (Fail-Closed)

With `--ext-static=required`, build fails if:

- no valid extensions are found
- manifest is invalid
- extension C source fails to compile
- extension link phase fails

This is intentional: no silent fallback.
