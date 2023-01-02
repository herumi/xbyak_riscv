import sys
isXbyak = True

def putRRR(name):
  if isXbyak:
    print(f'{name}(x1, x2, x3); dump1();')
  else:
    print(f'{name.strip("_")} x1, x2, x3')

def putRRI(name):
  if isXbyak:
    print(f'{name}(x1, x2, 1234); dump1();')
    print(f'{name}(x1, x2, -1234); dump1();')
  else:
    print(f'{name.strip("_")} x1, x2, 1234')
    print(f'{name.strip("_")} x1, x2, -1234')

def put(name):
  if isXbyak:
    print(f'{name}(); dump1();')
  else:
    print(f'{name}')

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
