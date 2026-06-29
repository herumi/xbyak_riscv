
# Xbyak_riscv 1.31 [![Badge Build]][Build Status]

*A C++ JIT assembler for RISC-V (under CONSTRUCTION)*

## Menu

- [Install]
- [Usage]
- [Changelog]

## Abstract

Xbyak_riscv is a C++ header library that enables dynamically to assemble RISC-V instructions.

## Feature

### B extension (Zba/Zbb/Zbc/Zbs)

The scalar bit-manipulation instructions (`andn`, `clz`, `min`, `rol`, `clmul`,
`bclr`, ... ) are available.

The pseudo instructions `sext_b`, `sext_h`, `zext_h`, and `zext_w` are encoded as
a base-ISA shift sequence by default so that the generated code runs on cores
without the B extension. Call `supportBext(true)` to emit the native B-extension
instruction (`sext.b`, `zext.w`, ...) instead.

```cpp
sext_b(a0, a1);              // slli; srai (base ISA)
supportBext(true);
sext_b(a0, a1);              // sext.b a0, a1 (Zbb)
supportBext(false);          // back to the base-ISA sequence
```

On Windows, define `NOMINMAX` before including `<windows.h>` so that `min` and
`max` are not turned into macros that clash with the `min`/`max` mnemonics.

## Supported Compilers

C++11 or later compiler

## Sample
Install QEMU and C++ compiler for RISC-V.
```
sudo apt install g++-14-riscv64-linux-gnu binutils-riscv64-unknown-elf
make -C sample
```
Generate targets:
```
cmake -DCMAKE_BUILD_TYPE=Debug -DXBYAK_RISCV_V=ON ..
```
Build:
```
make --build .  --parallel 4
```

## Test
```
make -C test
```
The vector test (`make -C test test_vec`) generates RVV instructions from
`gen/rvv_instr_dict.yaml` and compares xbyak's encoding against the assembler.
It uses the `Zvfbfwma` extension (`vfwmaccbf16`), which requires **binutils 2.43
or later** and PyYAML:
```
sudo apt install python3-yaml
```
The binutils packaged with Ubuntu 24.04 (2.42) cannot assemble `Zvfbfwma`; use a
distribution that ships binutils >= 2.43 (e.g. `debian:testing`) or build it from
source.

`test/run_vec_docker.sh` is a script for running and testing new binutils in Docker.

## License

[BSD-3-Clause License](http://opensource.org/licenses/BSD-3-Clause)

## Author

#### 光成滋生 Mitsunari Shigeo
 [GitHub](https://github.com/herumi) | [Website (Japanese)](http://herumi.in.coocan.jp/) | [herumi@nifty.com](mailto:herumi@nifty.com)

Thanks to [pazamelin](https://github.com/pazamelin) for the tremendous contribution.

## Sponsors welcome
[GitHub Sponsor](https://github.com/sponsors/herumi)

<!----------------------------------------------------------------------------->

[Badge Build]: https://github.com/herumi/xbyak_riscv/actions/workflows/main.yml/badge.svg
[Build Status]: https://github.com/herumi/xbyak_riscv/actions/workflows/main.yml

[License]: COPYRIGHT

[Changelog]: doc/changelog.md
[Install]: doc/install.md
[Usage]: doc/usage.md

