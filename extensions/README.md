# Static Extensions Directory

Tyrion discovers static extensions from `./extensions` by default.

Each extension should live under:

- `extensions/<name>/ext.toml`
- `extensions/<name>/src/*.c`
- Optional stdlib wrapper: `extensions/<name>/wrapper.ty`

When building with `--backend=tyrionc` and `--ext-static=auto|required`, if `--with-stdlib` is
not provided, Tyrion auto-discovers `extensions/*/wrapper.ty` and applies wrapper lowering.

Build example:

```bash
./tyrionc --build examples/foobar_static_ext_demo/foobar_static_ext.ty --out /tmp/foobar_demo
```

(When `--ext-dir` is omitted, the compiler uses `./extensions`.)
