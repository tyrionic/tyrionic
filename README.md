# Tyrionic Compiler

This repository contains the Tyrionic compiler written in Tyrionic.

## Bootstrap

The initial compiler is built with
[tyrionc](https://github.com/tyrionic/tyrionc), a small C seed compiler and
historical archive of the initial Tyrionic sources. Clone both repositories
beside each other:

```sh
git clone https://github.com/tyrionic/tyrionc.git
git clone https://github.com/tyrionic/tyrionic.git
```

Build the C seed:

```sh
make -C tyrionc
mkdir -p tyrionic/build
```

Use the seed to compile the Tyrionic source into the first-generation compiler:

```sh
./tyrionc/build/tyrionc \
  --selfhost-cli ./tyrionic/tyrionc.ty \
  --build ./tyrionic/tyrionc.ty \
  --out ./tyrionic/build/c1
```

Build the successor compiler:

```sh
./tyrionic/build/c1 \
  --build ./tyrionic/tyrionc.ty \
  --out ./tyrionic/build/c2
```

Use the successor to build the final Tyrionic compiler:

```sh
./tyrionic/build/c2 \
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
