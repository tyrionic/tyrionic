# Tyrion

Tyrion is a Python-flavored language that compiles `.ty` programs into native executables.
The distributed compiler is `tyrionc` (published as platform binaries in GitHub Releases).

## Quick Start

1. Download the correct compiler binary from Releases.
2. Mark it executable:

```bash
chmod +x ./tyrion_macos_aarch64
```

3. Create a program:

```python
# hello.ty
print("hello from Tyrion")
```

4. Build and run:

```bash
./tyrion_macos_aarch64 --build hello.ty --out hello
./hello
```

## Compile Commands

Core build command:

```bash
./tyrionc --build <input.ty> --out <output-bin>
```

Deterministic naming:

```bash
./tyrionc --build app.ty --out app --deterministic
```

## Extensions

Tyrion can include extensions from `./extensions` during build.

Common extension flags:

- `--ext-static=off|auto|required`
- `--ext-dir <path>`
- `--with-stdlib=<path>`

Typical build with extensions:

```bash
./tyrionc --build app.ty --out app --ext-static=auto
```

Require extensions (fail closed if missing/invalid):

```bash
./tyrionc --build app.ty --out app --ext-static=required --ext-dir ./extensions
```

Inject wrapper source:

```bash
./tyrionc --build app.ty --out app --ext-static=required --with-stdlib=./extensions/foobar/wrapper.ty
```

Detailed extension ABI and manifest format: `documentation/ABI.md`.

## Language Specifics

Core syntax/features:

- Primitive values: `int`, `float`, `str`, `bool`, `none`
- Arithmetic and comparisons: `+ - * /`, `== != < <= > >=`
- Collections: lists, tuples, dicts, sets
- Indexing/slicing: `x[0]`, `x[1:3]`
- Control flow: `if/elif/else`, `while`, `for`
- Guards: `stmt if cond`, `stmt unless cond`
- Functions and lambdas
- Classes and methods
- Exceptions: `try/except/finally`, `raise`
- File I/O with `open(..., "r"|"w")`

## Blocks and Guard Clauses

Tyrion supports both Python-style indentation and brace-style blocks (`{ ... }`) for control flow, functions, and classes.

Ruby-style guard clauses are also supported:

- `statement if condition`
- `statement unless condition`

### Example: Braces (`{}`) Blocks

```python
count = 3
while count > 0 {
    print("tick", count)
    count = count - 1
}

if count == 0 {
    print("done")
} else {
    print("not done")
}
```

### Example: Ruby-Style Guard Clauses

```python
enabled = True
print("feature enabled") if enabled
print("feature disabled") unless enabled

def positive_or_none(v):
    return unless v > 0
    return v
```

### Example: Class with Braces + Guards

```python
class Counter {
    def __init__(self, start) {
        self.value = start
    }

    def add(self, amount) {
        return unless amount > 0
        self.value = self.value + amount
    }

    def show(self) {
        print("counter", self.value) if self.value >= 0
    }
}

c = Counter(1)
c.add(4)
c.show()
```

### Example: Collections + Loop

```python
nums = [1, 2, 3, 4]
total = 0

for n in nums:
    total = total + n

print("sum =", total)
print("slice =", nums[1:3])
```

### Example: Function + Class

```python
def add(a, b):
    return a + b

class Greeter:
    def __init__(self, name):
        self.name = name
    def greet(self, other):
        print("Hello", other, "I am", self.name)

g = Greeter("Tyrion")
g.greet("World")
print("add:", add(3, 4))
```

### Example: Exceptions

```python
def risky(v):
    if v < 0:
        raise "negative"
    return v

try:
    print(risky(-1))
except negative as err:
    print("caught:", err)
finally:
    print("done")
```

## Notes and Current Limits

- Tyrion is compile-first through `--build`.
- Static extension support is available through `extensions/`.
- `next` / `continue` are not currently loop-control keywords.
  Use explicit guards/conditions inside loop bodies.
