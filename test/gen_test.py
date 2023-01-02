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

  misc()


if __name__ == '__main__':
  main()
