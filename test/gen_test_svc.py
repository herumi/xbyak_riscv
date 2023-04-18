import sys
from gen_test import *

def lwTest():
  for i in range(32):
    putRM('lw', f'x{i}', 'x9', 4)
  for i in range(0, 128+4, 4):
    putRM('lw', 'x8', 'x10', i)
  for i in range(32):
    putRM('lw', f'x3', 'sp', i)
  putRM('lw', f'x3', 'sp', 256-4)
  putRM('lw', f'x3', 'sp', 256)

  for i in range(32):
    putRM('ld', f'x{i}', 'x9', 8)
  for i in range(0, 256+8, 8):
    putRM('ld', 'x8', 'x10', i)
  for i in range(32):
    putRM('ld', f'x3', 'sp', i)
  putRM('ld', f'x3', 'sp', 512-8)
  putRM('ld', f'x3', 'sp', 512)

  for i in range(32):
    putRM('sw', f'x{i}', 'x9', 4)
  for i in range(0, 128+4, 4):
    putRM('sw', 'x8', 'x10', i)
  for i in range(32):
    putRM('sw', f'x3', 'sp', i)
  putRM('sw', f'x3', 'sp', 256-4)
  putRM('sw', f'x3', 'sp', 256)

  for i in range(32):
    putRM('sd', f'x{i}', 'x9', 8)
  for i in range(0, 256+8, 8):
    putRM('sd', 'x8', 'x10', i)
  for i in range(32):
    putRM('sd', f'x3', 'sp', i)
  putRM('sd', f'x3', 'sp', 512-8)
  putRM('sd', f'x3', 'sp', 512)

def immTest():
  # c.addi4spn
  for i in range(32):
    put('addi', f'x{i}, x2, 4')
  for i in range(32):
    put('addi', f'x2, x{i}, 8')
  for i in range(11):
    put('addi', f'a3, x2, {1<<i}')
  for i in range(0, 1028, 4):
    put('addi', f'a7, x2, {i}')
  put('nop')
  # c.addi
  for i in range(32):
    put('addi', f'x{i}, x{i}, 4')
  for i in range(-33, 33):
    put('addi', f'a3, a3, {i}')
  # c.addi16sp
  for i in range(-512-16, 496 + 16*2, 16):
    put('addi', f'x2, x2, {i}')
  # c.addiw
  for i in range(32):
    put('addiw', f'x{i}, x{i}, 4')
  for i in range(-33, 33):
    put('addiw', f'a3, a3, {i}')
  # c.li
  for i in range(-33,33):
    put('li', f'x5, {i}')
  # c.lui
  for i in range(34):
    put('lui', f'x5, {i}')
  for i in range((1<<20)-33,(1<<20)):
    put('lui', f'x5, {i}')
  # c.srli, c.srai, c.slli, c.andi
  for op in ['srli', 'srai', 'slli', 'andi']:
    for i in range(10):
      put(op, f'a3, a3, {i}')
    for i in range(4,10):
      put(op, f'x{i}, x{i}, 4')

def noimmTest():
  # c.sub
  tbl = ['sub', 'xor_', 'or_', 'and_', 'subw', 'addw', 'add']
  for name in tbl:
    for i in range(32):
      put(name, f'x{i}, x{i}, x9')

def miscTest():
  put('ebreak')

def main():
  if len(sys.argv) > 1 and sys.argv[1] == 'gas':
    setXbyak(False)
  if getXbyak():
    print('supportRVC();')

  lwTest()
  immTest()
  noimmTest()
  miscTest()

if __name__ == '__main__':
  main()
