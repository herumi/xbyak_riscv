import sys
import re

def bin2hex(m):
  return m.group(1) + hex(int(m.group(2), 2))

def main():
  if len(sys.argv) == 1:
    print('bin2hex.py filename')
    return
  name = sys.argv[1]
  text = ''
  with open(name) as f:
    text = f.read()
    text = re.sub(r'([^0-9a-f])(0b[01]+)', bin2hex, text)
  with open(name, 'w') as f:
    f.write(text)

main()
