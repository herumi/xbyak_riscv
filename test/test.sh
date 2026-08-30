#!/usr/bin/bash
set -e
ASFLAGS="-march=rv64imafdqv"
case $1 in
svc)
  echo "svc test"
  ASFLAGS+="c"
  GEN=gen_test_svc.py
  ;;
vec)
  echo "vec test"
  ASFLAGS+="_zvfbfmin_zvfbfwma"
  GEN=gen_test_vec.py
  ;;
li|li_bext|li_rv32)
  # li expansion is compared with llvm-mc
  echo "$1 test"
  GEN="gen_test_li.py $1"
  LLVM_MC=${LLVM_MC:-$(command -v llvm-mc || ls /usr/lib/llvm-*/bin/llvm-mc 2>/dev/null | sort -V | tail -1)}
  if [ -z "$LLVM_MC" ]; then
    echo "llvm-mc is not found. skip"
    exit 0
  fi
  MATTR="+m"
  TRIPLE=riscv64
  case $1 in
  li_bext) MATTR+=",+zba,+zbb,+zbs" ;;
  li_rv32) TRIPLE=riscv32 ;;
  esac
  ;;
*)
  echo "test"
  GEN=gen_test.py
  ;;
esac

ASFLAGS+="_zba_zbb_zbc_zbs_zifencei"

CXX=${CXX:-g++}
AS=${AS:-riscv64-linux-gnu-as}
OBJDUMP=${OBJDUMP:-riscv64-unknown-elf-objdump}
CFLAGS="-g -I../ -Wall -Wextra"
CFLAGS+=" -DXBYAK_RISCV_V"

python3 $GEN gas > generated.s
if [ -n "$LLVM_MC" ]; then
  echo $LLVM_MC -triple=$TRIPLE -mattr=$MATTR -filetype=obj -o generated.o generated.s
  $LLVM_MC -triple=$TRIPLE -mattr=$MATTR -filetype=obj -o generated.o generated.s
else
  echo $AS -c -o generated.o generated.s $ASFLAGS
  $AS -c -o generated.o generated.s $ASFLAGS
fi
$OBJDUMP --no-addresses -d generated.o | sed -e '1,7d' > ok.s
awk '/        / { print $1 }' < ok.s > ok.txt

python3 $GEN > generated.cpp
$CXX $CFLAGS out.cpp
./a.out > my.txt

diff -urN ok.txt my.txt


