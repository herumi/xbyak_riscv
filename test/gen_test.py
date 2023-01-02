import sys
isXbyak = True

def put3r(name):
  if isXbyak:
    print(f'{name}(x1, x2, x3); dump1();')
  else:
    print(f'{name.strip("_")} x1, x2, x3')

def main():
  global isXbyak
  if len(sys.argv) > 1 and sys.argv[1] == 'gas':
    isXbyak = False

  for op in ['add', 'sub', 'sll', 'slt', 'sltu', 'xor_', 'srl', 'sra', 'or_', 'and_']:
    put3r(op)


if __name__ == '__main__':
  main()
