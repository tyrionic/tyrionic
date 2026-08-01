# Changelog

All notable changes to `tyrionic` are documented in this file.

This project follows semantic versioning.

## 0.1.5

Added:

- Add verified Linux x86-64 Native IR v2 direct lowering for aggregate
  ownership, generic iteration, assignment, expressions, functions and
  closures, classes, exceptions, generators, and compiler primitives.
- Add deterministic whole-program reachability for functions, callable
  descriptors, classes, attributes, constants, primitives, and AST-free
  runtime components.

Changed:

- Route Linux x86-64 applications and compiler descendants through
  source-specific Native IR v2 without an evaluator fallback or embedded
  static source token/AST image.
- Lower, verify, and emit Native IR v2 functions as a bounded stream, retaining
  only compact declarations, constants, and exact operation/primitive
  manifests, verify slot initialization with one all-slot CFG dataflow, and
  resolve scalar definitions, slot roots, callable declarations, and
  dominator-tree intervals through builder-backed indexes. Compute
  predecessors, reverse postorder, and immediate dominators once per function,
  answer dominance queries in constant time, propagate ownership state with a
  monotone changed-block worklist, and pass precomputed slot layout offsets to
  x86 instruction selection. Materialize deferred CFG edge patches through a
  per-block index, collect function and callable-name inventories through
  append-only builders, assemble module-graph source from append-only
  fragments using deterministic balanced joins, resolve module duplicate
  symbols through a deterministic hash with exact-byte collision checks
  instead of copying the owned symbol inventory per lookup, classify module
  source lines within the traversal frame, and lower contiguous frame and
  temporary cleanup to one verified range operation whose runtime loop
  preserves canonical per-slot ownership behavior.
- Index application callables with deterministic exact-byte collision checks
  and propagate non-returning calls through a reverse-dependency worklist
  instead of repeated whole-program scans.
- Keep target-specialized compiler-emitter branches mutually exclusive so
  Linux reachability does not retain the Darwin fallback after selecting the
  Linux emitter.

Fixed:

- Preserve signed 64-bit integer payloads through Linux x86-64 direct slot
  extraction, calls, arithmetic, and printing, including constants that require
  a 64-bit immediate materialization.
- Keep the example random extension's `rand_u64()` result within the
  non-negative range representable by Tyrion's signed 64-bit integer ABI.
- Extend Darwin owned heap-string normalization to compiler metadata and
  inventories, preserving results beyond legacy inline and 64 KiB storage
  limits.
- Remove the stale Linux x86-64 virtual-state allocation hook left behind by
  the native-backend cutover, keeping direct compiler descendants independent
  of the removed virtual-register runtime.

## 0.1.4

Added:

- Add a verified Linux x86-64 Native IR v2 direct-lowering path for scalar
  programs while retaining the established Native IR v1 production route.

Fixed:

- Publish long Darwin text-builder results with the canonical owned heap-string
  ABI, preserving output-path and `.tyn` metadata writes beyond inline storage.

## 0.1.3

Changed:

- Reduce Linux x86-64 compiler-generation time with a constant-depth token-pool
  hash while retaining exact-byte collision checks and deterministic offsets.

## 0.1.2

Changed:

- Store Linux x86-64 static source tokens in a versioned, pointer-free image
  with deterministic text deduplication while preserving the canonical runtime
  token ABI and ownership behavior.

Fixed:

- Materialize bounded NUL-terminated copies before passing length-addressed
  token text to `strtod`.

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
