import sys
isXbyak = True

def setXbyak(flag=True):
  global isXbyak
  isXbyak = flag

def getXbyak():
  return isXbyak

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

def addRM(rm):
  if isXbyak:
    return 'RM::' + rm
  return rm

def putFPU(name, arg, rm=""):
  if rm:
    arg += f', {addRM(rm)}'
  put(name, arg)

def putFFFF(name, nm=""):
  putFPU(name, 'f1, f2, f3, f4', nm)

def putFFF(name, nm=""):
  putFPU(name, 'f1, f2, f3', nm)

def putFF(name, nm=""):
  putFPU(name, 'f2, f3', nm)

def putFR(name, nm=""):
  putFPU(name, 'f1, x5', nm)

def putRF(name, nm=""):
  putFPU(name, 'x9, f10', nm)

def putRFF(name, nm=""):
  putFPU(name, 'x9, f10, f3', nm)

def putRR(name):
  put(name, 'x1, x2')

def putR(name):
  put(name, 'x12')

def putRRI(name):
  put(name, 'x1, x2, 1234')
  put(name, 'x1, x2, -1233')
  put(name, 'x1, x2, -2048')
  put(name, 'x1, x2, 2047')

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

def csr():
  def castCSR(x):
    return f'CSR({x})' if isXbyak else f'{x}'

  for op in ['csrrw', 'csrrs', 'csrrc']:
    put(op, f'x1, {castCSR(5)}, x7')

  for op in ['csrrwi', 'csrrsi', 'csrrci']:
    put(op, f'x10, {castCSR(9)}, 13')

  put('csrr', f'x2, {castCSR(1)}')
  for op in ['csrw', 'csrs', 'csrc']:
    put(op, f'{castCSR(2)}, x3')
  for op in ['csrwi', 'csrsi', 'csrci']:
    put(op, f'{castCSR(4)}, 9')

def fpu():
  tbl = ['fsgnj_s', 'fsgnjn_s', 'fsgnjx_s', 'fmin_s', 'fmax_s']
  for op in tbl:
    putFFF(op)

  tbl = ['fmv_x_w', 'fclass_s']
  for op in tbl:
    putRF(op)

  tbl = ['feq_s', 'flt_s', 'fle_s']
  for op in tbl:
    putRFF(op)

  tbl = ['fcvt_s_w', 'fcvt_s_wu', 'fmv_w_x']
  for op in tbl:
    putFR(op)

  rmTbl = ['rne', 'rtz', 'rdn', 'rup', 'rmm', 'dyn']
  for rm in rmTbl:
    tbl = ['fmadd_s', 'fmsub_s', 'fnmsub_s', 'fnmadd_s'] #, 'fmadd_h', 'fmsub_h', 'fnmsub_h', 'fnmadd_h']
    for op in tbl:
      putFFFF(op, rm)

    tbl = ['fadd_s', 'fsub_s', 'fmul_s', 'fdiv_s']
    for op in tbl:
      putFFF(op, rm)

    tbl = ['fcvt_l_s', 'fcvt_lu_s', 'fcvt_w_s', 'fcvt_wu_s']
    for op in tbl:
      putRF(op, rm)

    tbl = ['fcvt_s_l', 'fcvt_s_lu']
    for op in tbl:
      putFR(op, rm)

    tbl = ['fsqrt_s']
    for op in tbl:
      putFF(op, rm)

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

  csr()
  fpu()
  misc()


if __name__ == '__main__':
  main()
