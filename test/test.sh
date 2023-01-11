#!/usr/bin/bash
set -e
case $1 in
svc)
  echo "svc test"
  ASFLAGS="-march=rv64gc"
  GEN=gen_test_svc.py
  ;;
*)
  echo "test"
  ASFLAGS=""
  GEN=gen_test.py
  ;;
esac

CXX=g++
AS=riscv64-linux-gnu-as
OBJDUMP=riscv64-unknown-elf-objdump
CFLAGS="-I../ -Wall -Wextra"

python3 $GEN > generated.cpp
$CXX $CFLAGS out.cpp
./a.out > my.txt

python3 $GEN gas > generated.s
$AS -c -o generated.o generated.s $ASFLAGS
$OBJDUMP --no-addresses -d generated.o > ok.s
awk '/        / { print $1 }' < ok.s > ok.txt

diff -urN ok.txt my.txt


