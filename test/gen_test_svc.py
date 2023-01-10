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

def addTest():
  for i in range(32):
    put('addi', f'x{i}, x2, 4')
  for i in range(32):
    put('addi', f'x2, x{i}, 8')

def main():
  global isXbyak
  if len(sys.argv) > 1 and sys.argv[1] == 'gas':
    isXbyak = False
  if isXbyak:
    print('supportRVC();')

  addTest()

if __name__ == '__main__':
  main()
