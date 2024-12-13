
# Xbyak_riscv 0.01 [![Badge Build]][Build Status]

*A C++ JIT assembler for RISC-V (under CONSTRUCTION)*

## Menu

- [Install]
- [Usage]
- [Changelog]

## Abstract

Xbyak_riscv is a C++ header library that enables dynamically to assemble RISC-V instructions.

## Feature


## News


## Supported OS


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

