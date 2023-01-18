import sys
from gen_test import *

def lwTest():
  for i in range(32):
    putRM('lw', f'x{i}', 'x9', 4)
  for i in range(0, 128+4, 4):
    putRM('lw', 'x8', 'x10', i)

  for i in range(32):
    putRM('ld', f'x{i}', 'x9', 8)
  for i in range(0, 256+8, 8):
    putRM('ld', 'x8', 'x10', i)

  for i in range(32):
    putRM('sw', f'x{i}', 'x9', 4)
  for i in range(0, 128+4, 4):
    putRM('sw', 'x8', 'x10', i)

  for i in range(32):
    putRM('sd', f'x{i}', 'x9', 8)
  for i in range(0, 256+8, 8):
    putRM('sd', 'x8', 'x10', i)

def addTest():
  for i in range(32):
    put('addi', f'x{i}, x2, 4')
  for i in range(32):
    put('addi', f'x2, x{i}, 8')
  for i in range(11):
    put('addi', f'a3, x2, {1<<i}')
  for i in range(0, 1028, 4):
    put('addi', f'a7, x2, {i}')

def main():
  if len(sys.argv) > 1 and sys.argv[1] == 'gas':
    setXbyak(False)
  if getXbyak():
    print('supportRVC();')

  lwTest()
  addTest()

if __name__ == '__main__':
  main()
