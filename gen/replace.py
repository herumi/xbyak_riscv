import sys
from bit_pattern import *
FILE='../xbyak_riscv/xbyak_riscv.hpp'
KEY="// @@@ embedded by bit_pattern.py (DON'T DELETE THIS LINE)"
OUT=FILE

text=[]
with open(FILE) as f:
  text=f.read().split('\n')

ptnText=''
tbl = [
  '20|10:1|11|19:12|z12',# Jal imm
  '12|10:5|z13|4:1|11|z7', # Btype
  '5:4|9:6|2|3|z5',  # c.addi4spn
  '5:3|z3|2|6|z5',   # c.lw
  '5:3|z3|7|6|z5',   # c.ld
]
for ptn in tbl:
  ptnText += bitPattern(ptn) + '\n'

mode='start'
with open(OUT, 'w') as f:
  for line in text[:-1]:
    if mode == 'start':
      if line == KEY:
        mode = 'in'
        f.write(KEY + '\n')
        f.write(ptnText)
        f.write(KEY + '\n')
        continue
      else:
        f.write(line + '\n')
    elif mode == 'in':
      if line == KEY:
        mode = 'out'
    elif mode == 'out':
      f.write(line + '\n')
      
