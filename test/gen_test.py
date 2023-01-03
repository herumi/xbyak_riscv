import sys
isXbyak = True

def put(name, args=""):
  if isXbyak:
    print(f'{name}({args}); dump1();')
  else:
    print(f'{name.strip("_")} {args}')

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

def misc():
  put('ret')

def main():
  global isXbyak
  if len(sys.argv) > 1 and sys.argv[1] == 'gas':
    isXbyak = False

  for op in ['add', 'sub', 'sll', 'slt', 'sltu', 'xor_', 'srl', 'sra', 'or_', 'and_']:
    putRRR(op)

  for op in ['addi', 'slti', 'sltiu', 'xori', 'ori', 'andi', 'jalr']:
    putRRI(op)

  for op in ['lb', 'lh', 'lw', 'lbu', 'lhu']:
    putRM(op, 'x9', 'x3', 0)
    putRM(op, 'x1', 'x4', -4)
    putRM(op, 'x2', 'x5', 123)

  for op in ['lui']:
    putRI(op)

  misc()


if __name__ == '__main__':
  main()
