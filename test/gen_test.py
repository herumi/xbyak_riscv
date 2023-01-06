import sys
isXbyak = True

def putEach(op1, op2):
  if isXbyak:
    print(f'{op1};')
  else:
    print(op2)

def put(name, args=""):
  putEach(f'{name}({args})', f'{name.strip("_")} {args}')

def putRRR(name):
  put(name, 'x1, x2, x3')

def putRRI(name):
  put(name, 'x1, x2, 1234')
  put(name, 'x1, x2, -1234')

def putRM(name, rd, rs1, offset):
  if isXbyak:
    if offset == 0:
      args = f'{rd}, {rs1}'
    else:
      args = f'{rd}, {rs1}, {offset}'
  else:
    if offset == 0:
      args = f'{rd}, ({rs1})'
    else:
      args = f'{rd}, {offset}({rs1})'
  put(name, args)

def putRI(name):
  put(name, 'x2, 1234')
  put(name, f'x31, {(1<<20)-1}')

def putFence():
  putEach('fence_rw_rw()', 'fence rw, rw')
  putEach('fence_tso()', 'fence.tso')
  putEach('fence_rw_w()', 'fence rw, w')
  putEach('fence_r_rw()', 'fence r, rw')
  putEach('fence_r_r()', 'fence r, r')
  putEach('fence_w_w()', 'fence w, w')
  putEach('fence_i()', 'fence.i')

def putJmp(name):
  n = 32
  putEach(f'Label B{name} = L(), F{name};', f'B{name}:')
  for i in range(n):
    if name == 'jal':
      put(name, f'x{i}, B{name}')
      put(name, f'x{i}, F{name}')
    else:
      put(name, f'x{i},x5, B{name}')
      put(name, f'x{i},x2, F{name}')
  putEach(f'L(F{name});', f'F{name}:')

def misc():
  for name in ['ret', 'ecall', 'ebreak']:
    put(name)

def main():
  global isXbyak
  if len(sys.argv) > 1 and sys.argv[1] == 'gas':
    isXbyak = False

  for op in ['add', 'sub', 'sll', 'slt', 'sltu', 'xor_', 'srl', 'sra', 'or_', 'and_']:
    putRRR(op)

  for op in ['addi', 'slti', 'sltiu', 'xori', 'ori', 'andi', 'jalr']:
    putRRI(op)

  for op in ['lb', 'lh', 'lw', 'lbu', 'lhu', 'sb', 'sh', 'sw', 'lwu', 'ld']:
    putRM(op, 'x9', 'x3', 0)
    putRM(op, 'x1', 'x4', -4)
    putRM(op, 'x2', 'x5', 123)
    putRM(op, 'x31', 'x7', (1<<11)-1)
    putRM(op, 'x31', 'x7', -(1<<11))

  for op in ['lui', 'auipc']:
    putRI(op)

  for op in ['slli', 'srli', 'srai']:
    put(op, 'x1, x2, 1')
    put(op, 'x15, x20, 63')

  putFence()
  for op in ['jal', 'beq', 'bne', 'blt', 'bge', 'bltu', 'bgeu']:
    putJmp(op)

  misc()


if __name__ == '__main__':
  main()
