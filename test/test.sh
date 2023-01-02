#!/usr/bin/bash
CXX=g++
AS=riscv64-linux-gnu-as
OBJDUMP=riscv64-unknown-elf-objdump
CFLAGS=-I../

python3 gen_test.py > generated.cpp
$CXX $CFLAGS out.cpp
./a.out > my.txt

python3 gen_test.py gas > a.s
$AS -c -o a.o a.s
$OBJDUMP --no-addresses -d a.o > ok.s
awk '/        / { print $1 }' < ok.s > ok.txt

diff ok.txt my.txt


