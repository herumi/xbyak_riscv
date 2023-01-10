import sys
isXbyak = True

def putEach(op1, op2):
  if isXbyak:
    print(f'{op1};')
  else:
    print(op2)

def put(name, args=""):
  asmName = name.strip('_').replace('_', '.')
  putEach(f'{name}({args})', f'{asmName} {args}')

def putRRR(name):
  put(name, 'x1, x2, x3')

def putRR(name):
  put(name, 'x1, x2')

def putR(name):
  put(name, 'x12')

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
  put('fence')

def putJmp(name, paraN):
  n = 32
  putEach(f'Label B{name} = L(), F{name}', f'B{name}:')
  for i in range(n):
    if paraN == 0:
      args = ''
    elif paraN == 1:
      args = f'x{i}, '
    elif paraN == 2:
      args = f'x{i}, x{(i+1)%n}, '
    put(name, f'{args}B{name}')
    put(name, f'{args}F{name}')
  putEach(f'L(F{name})', f'F{name}:')

def putAtomic(name, suf, flag):
  rs1 = 'x1'
  rs2 = 'x10'
  rd = 'x20'
  if isXbyak:
    if flag:
      flag = ', T_' + flag
    print(f'{name}_{suf}({rd}, {rs2}, {rs1}{flag});')
  else:
    if flag:
      flag = '.' + flag
    print(f'{name}.{suf}{flag} {rd}, {rs2}, ({rs1})')

def putLr(suf, flag):
  rs1 = 'x1'
  rd = 'x20'
  if isXbyak:
    if flag:
      flag = ', T_' + flag
    print(f'lr_{suf}({rd}, {rs1}{flag});')
  else:
    if flag:
      flag = '.' + flag
    print(f'lr.{suf}{flag} {rd}, ({rs1})')

def misc():
  for name in ['ret', 'ecall', 'ebreak', 'nop']:
    put(name)
  for name in ['mv', 'not_', 'neg', 'negw', 'sext_b', 'sext_h', 'sext_w', 'zext_b', 'zext_h', 'zext_w',
    'seqz', 'snez', 'sltz', 'sgtz',
  ]:
    putRR(name)

def main():
  global isXbyak
  if len(sys.argv) > 1 and sys.argv[1] == 'gas':
    isXbyak = False

  for op in ['add', 'sub', 'sll', 'slt', 'sltu', 'xor_', 'srl', 'sra', 'or_', 'and_', 'addw', 'subw', 'sllw', 'srlw', 'sraw',
    'mul', 'mulh', 'mulhsu', 'mulhu', 'div', 'divu', 'rem', 'remu',
    'mulw','divw', 'remw', 'remuw',
  ]:
    putRRR(op)

  for op in ['addi', 'slti', 'sltiu', 'xori', 'ori', 'andi', 'jalr', 'addiw']:
    putRRI(op)

  for op in ['lb', 'lh', 'lw', 'lbu', 'lhu', 'sb', 'sh', 'sw', 'lwu', 'ld', 'sd']:
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

  for op in ['slliw', 'srliw', 'sraiw']:
    put(op, 'x1, x2, 1')
    put(op, 'x15, x20, 31')

  putFence()

  putJmp('j_', 0)
  for op in ['jal', 'beqz', 'bnez', 'blez', 'bgez', 'bgtz']:
    putJmp(op, 1)
  for op in ['beq', 'bne', 'blt', 'bge', 'bltu', 'bgeu', 'bgt', 'ble', 'bgtu', 'bleu']:
    putJmp(op, 2)

  for op in ['jr', 'jalr']:
    putR(op)

  for flag in ['', 'aq', 'rl', 'aqrl']:
    for op in ['sc', 'amoswap', 'amoadd', 'amoxor', 'amoand', 'amoor', 'amomin', 'amomax', 'amominu', 'amomaxu']:
      putAtomic(op, 'w', flag)
      putAtomic(op, 'd', flag)
    putLr('w', flag)
    putLr('d', flag)

  misc()


if __name__ == '__main__':
  main()
