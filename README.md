<p align="center">
  <img src="https://raw.githubusercontent.com/tyrionic/tyrionic/refs/heads/main/assets/img/tyrion.jpg" width="800" alt="Tyrion: a small yet capable programming language" />
</p>

# Tyrion Compiler

Tyrion is a Python-flavored programming language with a strong focus on practical native compilation and self-hosting.
Its syntax is familiar and lightweight, while the compiler targets standalone native executables.

This `tyrionic/` repository is the distribution repo for Tyrion compiler artifacts and companion sources:

- compiler binaries are published in GitHub Releases
- `tyrionc.ty`: Tyrion compiler source
- `extensions/`: static extension modules for host ABI integration

## Supported Targets

- Linux `x86_64`
- Linux `aarch64`
- macOS `aarch64` (Mach-O / Apple Silicon)

## Getting Started

1. Download the right compiler binary from GitHub Releases.
2. Make it executable (`chmod +x <binary>`).
3. Compile a Tyrion program:
   - `./<compiler> --build hello.ty --out hello`
4. Run the result:
   - `./hello`

For more advanced usage (extensions and strict native mode), see the main project documentation.
