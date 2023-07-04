#!/usr/bin/bash
set -e
case $1 in
svc)
  echo "svc test"
  ASFLAGS="-march=rv64iafmqgc"
  GEN=gen_test_svc.py
  ;;
*)
  echo "test"
  ASFLAGS="-march=rv64iafmqg"
  GEN=gen_test.py
  ;;
esac

CXX=g++
AS=riscv64-linux-gnu-as
OBJDUMP=riscv64-unknown-elf-objdump
CFLAGS="-g -I../ -Wall -Wextra"

python3 $GEN gas > generated.s
$AS -c -o generated.o generated.s $ASFLAGS
$OBJDUMP --no-addresses -d generated.o | sed -e '1,7d' > ok.s
awk '/        / { print $1 }' < ok.s > ok.txt

python3 $GEN > generated.cpp
$CXX $CFLAGS out.cpp
./a.out > my.txt

diff -urN ok.txt my.txt


