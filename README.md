# Tyrionic Compiler

This repository contains the Tyrionic compiler written in Tyrionic.

## Bootstrap

The initial compiler is built with the
[Tyrionic Bootstrap Compiler](https://github.com/tyrionic/tyrionic-bootstrap-compiler),
a small C seed compiler. Clone both repositories beside each other:

```sh
git clone https://github.com/tyrionic/tyrionic-bootstrap-compiler.git
git clone https://github.com/tyrionic/tyrionic.git
```

Build the C seed:

```sh
make -C tyrionic-bootstrap-compiler
mkdir -p tyrionic/build
```

Use the seed to compile the Tyrionic source into the first-generation compiler:

```sh
./tyrionic-bootstrap-compiler/build/tyrionc \
  --selfhost-cli ./tyrionic/tyrionc.ty \
  --build ./tyrionic/tyrionc.ty \
  --out ./tyrionic/build/tyrionc_bootstrapper
```

Use the resulting compiler to produce the second generation:

```sh
./tyrionic/build/tyrionc_bootstrapper \
  --build ./tyrionic/tyrionc.ty \
  --out ./tyrionic/build/tyrionic
```

`build/tyrionic` is the bootstrapped Tyrionic compiler. It can compile Tyrionic
programs directly:

```sh
./tyrionic/build/tyrionic \
  --build ./program.ty \
  --out ./program
```
