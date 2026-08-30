import sys
import random
from gen_test import *

# li x10, imm : compared with llvm-mc (RISCVMatInt::generateInstSeq)
# usage : python3 gen_test_li.py <li|li_bext|li_rv32> [gas]

def values64():
  v = [0, 1, -1, 2, -2, 0x7ff, -0x800, 0x800, -0x801, 0xfff, 0x1000, 0x17ff, 0x1800, 0xfffff, -0xfffff, 0x1fffff, -0x1fffff, 0x7ffff000, 0x7fffffff, 0x80000000, -0x80000000, -0x80000001,
    0xffffffff, 0x100000000, 0x100000001, 0x7fffffffffffffff, 0x8000000000000000, -1 << 63, 0xffffffff80000000,
    0x0123456789abcdef, 0x123456789abcdef0, 0xdeadbeef, 0xdeadbeef0000, 0xdeadbeef00000000, 0x0000ffffffffffff, 0x000fffffffffffff,
    0x00ffffff00000000, 0xffff0000ffff0000, 0x123456789, 0x1ffffffff, 0x1fffffffff, 0xfffffffffff00000, 0x00007fffffff8000, 0x123450000000,
    0xfffff000, 0x800000000000, 0x7ffffabc, 0x7ffffffe, 0x12345000, 0x12348000, 0xff00ff00ff00ff00, 0x00ff00ff00ff00ff, 0x5555555555555555,
    0xaaaaaaaaaaaaaaaa, 0x8000000000000001, 0x0000000100000000, 0xfffffffeffffffff, 0x1234567800000000, 0x0000123400001234,
    0x00000000ffff17ff, 0x00000001000017ff, 0x00000000000017ff, 0xffffffffffff17ff, 0x7fffffff17ff17ff,
  ]
  # multiples of 3, 5, 9 (Zba sh*add)
  for d in [3, 5, 9]:
    for x in [0x12345678, 0x7fffffff, -0x80000000, 0x40000000, 0x1234, -0x1234]:
      v.append(x * d)
      v.append(x * d + 0x123)
      v.append(x * d - 0x123)
  # rotated 12-bit values (Zbb rori)
  for x in [1, 0x7ff, -0x800, -1, 0x555, -0x556]:
    for r in [1, 8, 12, 31, 32, 33, 52, 63]:
      v.append(((x << r) | ((x & 0xffffffffffffffff) >> (64 - r))) & 0xffffffffffffffff)
  # single bit, two bits (Zbs bseti/bclri)
  for i in range(64):
    v.append(1 << i)
    v.append(~(1 << i))
    v.append((1 << i) | 1)
    v.append((1 << i) | (1 << 31))
  r = random.Random(12345)
  for i in range(300):
    v.append(r.getrandbits(64))
  # contiguous bit runs and sparse bits
  for i in range(300):
    a = r.randrange(64)
    b = r.randrange(64)
    lo, hi = min(a, b), max(a, b)
    x = ((1 << (hi - lo + 1)) - 1) << lo
    v.append(x)
    v.append(~x)
    v.append(x ^ r.getrandbits(12))
  for i in range(200):
    x = 0
    for j in range(r.randrange(1, 5)):
      x |= 1 << r.randrange(64)
    v.append(x)
    v.append(~x)
  # shifted 32-bit values
  for i in range(200):
    x = r.getrandbits(32)
    if r.randrange(2):
      x -= 1 << 32
    v.append(x << r.randrange(33))
  return v

def main():
  mode = sys.argv[1]
  if len(sys.argv) > 2 and sys.argv[2] == 'gas':
    setXbyak(False)
  rv32 = mode == 'li_rv32'
  if getXbyak():
    if rv32:
      print('setRV32();')
    if mode == 'li_bext':
      print('supportBext();')
  seen = set()
  for v in values64():
    v &= 0xffffffffffffffff
    if rv32:
      # 32-bit values only (sign-extended)
      v &= 0xffffffff
      if v >= 1 << 31:
        v -= 1 << 32
    if v in seen:
      continue
    seen.add(v)
    put('li', f'x10, {v:#x}')

if __name__ == '__main__':
  main()
