# Changelog

All notable changes to `tyrionic` are documented in this file.

This project follows semantic versioning.

## 0.1.1

Added:

- A fully native Linux x86-64 compiler backend using the System V AMD64 ABI,
  RIP-relative addressing, native stack frames, and direct runtime calls.
- Native x86-64 expression and statement execution for collections,
  comprehensions, indexing, slicing, branches, loops, exceptions, functions,
  recursion, default arguments, and keyword arguments.
- Native compiler primitives for files, module loading, process execution,
  static extensions, TCP sockets, terminal input, and ANSI escape sequences.
- Native ownership support for strings, collections, closures, objects,
  writers, AST builders, files, and TCP handles.
- Deterministic C seed to c1 to c2 to c3 to c4 fixed-point verification and
  cross-generation application, extension, diagnostic, and ownership tests.

Changed:

- Linux x86-64 compilation now exclusively uses target-native lowering. The
  virtual AArch64 register machine and compatibility translation route have
  been removed.
- The compiler backend now uses canonical native IR, value slots, AST records,
  function dispatch, and capability-driven runtime component selection.
- Linux x86-64 terminal input now exposes normalized key events including
  UTF-8 text, raw sequences, function keys, arrows, and modifier state.
- CLI help now consistently identifies the compiler executable as `tyrionic`.

Fixed:

- Correct high-address heap-string copies in generated Darwin executables.
- Correct nested compiler AST-builder behavior during descendant compilation.
- Preserve target-emitter dependencies and parse compiler source into canonical
  AST records before descendant compiler emission.
- Keep target-specific assembly formatting isolated to its target backend and
  emit valid Darwin stack-pointer arithmetic during descendant generation.
- Correct the native x86-64 `zip()` call-frame argument-count slot.
- Initialize copy-on-write mutation temporaries before every release path,
  eliminating uninitialized ownership checks during nested collection
  mutation.

## 0.1.0

Added:

- Initial release of the tyrionic compiler written in Tyrionic
