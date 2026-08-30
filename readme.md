
# Xbyak_riscv 1.34 [![Badge Build]][Build Status]

*A C++ JIT assembler for RISC-V (under CONSTRUCTION)*

## Menu

- [Install]
- [Usage]
- [Changelog]

## Abstract

Xbyak_riscv is a C++ header library that enables dynamically to assemble RISC-V instructions.

## News
Breaking change: `li(rd, u64imm)` supports 64-bit unsigned imm and it breaks backward compatibility of the old `li(rd, u32imm)`.
Define `XBYAK_RISCV_LI_OLD` to use the old li. See [64-bit immediate (`li`)](#64-bit-immediate-li).

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

### Far jump to a label (`call`, `tail`, `jump`, `la`)

`jal`/`j_` take a 21-bit offset (+-1MiB) and the branch instructions take a
13-bit offset (+-4KiB); an exception is thrown if the label is out of range.
The pseudo instructions `call`, `tail`, and `jump` are expanded to
`auipc` + `jalr` (8 bytes, +-2GiB) in the same way as gas:

```cpp
call(label, rd = x1);// auipc rd, hi ; jalr rd, lo(rd)
tail(label);         // auipc x6, hi ; jalr x0, lo(x6)
jump(label, rt);     // auipc rt, hi ; jalr x0, lo(rt)
la(label, rd);       // auipc rd, hi ; addi rd, rd, lo (rd = address of label)
```

Note that `tail` clobbers `x6` (t1). `call(label, rd)` uses `rd` itself as the
scratch register, whereas gas `call rd, label` uses `x6`.

If the label is already defined (a backward reference) and within +-1MiB,
`call`, `tail` and `jump` emit a single `jal` (4 bytes) instead.
With `supportRVC(true)`, a backward jump/branch to a label in range is also compressed:
`j_`/`tail`/`jump` to `c.j` (+-2KiB), `call`/`jal(x1, label)` to `c.jal` (RV32 only),
and `beqz`/`bnez` with `x8`-`x15` to `c.beqz`/`c.bnez` (+-256B).
A forward reference is never shortened.
Since a 2-byte instruction changes the alignment of the following code,
use `align()` if you put data after the code.

### 64-bit immediate (`li`)

`li(rd, imm)` takes a 64-bit immediate and expands it in the same way as LLVM
(`RISCVMatInt::generateInstSeq`): `lui`/`addiw` for a signed 32-bit value,
otherwise `slli`/`srli`/`addi`/`xori` sequences using `rd` only (at most 8
instructions). With `supportBext(true)`, Zba/Zbb/Zbs instructions (`bseti`,
`bclri`, `slli.uw`, `zext.w`, `sh1add`, `rori`, ...) are also used. On RV32
(`setRV32()`), `imm` must be a 32-bit value (zero- or sign-extended); otherwise
an exception is thrown.

```cpp
li(a0, 0x12345678);         // lui a0, 0x12345 ; addiw a0, a0, 0x678
li(a0, 0xffffffff);         // addi a0, zero, -1 ; srli a0, a0, 32
li(a0, 0x123450000000);     // lui a0, 0x12345 ; slli a0, a0, 16
li(a0, 0xffffffff80000000); // lui a0, 0x80000
supportBext(true);
li(a0, 0x8000000000000000); // bseti a0, zero, 63
```

Note that `li` took a `uint32_t` before ver 1.34 and a 32-bit value with bit 31
set was sign-extended on RV64 (`li(a0, 0x80000000)` was `lui a0, 0x80000`).
Define `XBYAK_RISCV_LI_OLD` to restore that behavior temporarily; it will be
removed in the future.

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

