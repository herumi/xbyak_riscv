def bitPattern(ptn):
  """
  ptn is bit pattern
  mask(n) = (1 << n) - 1
  {a}     => 1<<a
  {a}:{b} => mask(a-b+1)<<b
  z{a}    => a-bit zero
  5:2|7:6 => (mask(5-2+1)<<2) concat (mask(5-6+1)<<6)
  """
  ret=f'inline size_t get{ptn.replace("|", "_").replace(":", "to")}(size_t v) {{ return '
  v = []
  pos = 0
  for e in reversed(ptn.split('|')):
    if ':' in e:
      ab = e.split(':')
      a = int(ab[0])
      b = int(ab[1])
    elif 'z' in e:
      a = -1
      b = -int(e[1:])
    else:
      a = b = int(e)
    v.append((a, b, pos))
    pos += a-b+1
  first = True
  for (a, b, pos) in reversed(v):
    if a < 0:
      continue
    if first:
      first = False
    else:
      ret += '| '
    shift = pos - b
    if b == 0:
      mask = f'(v & {2**(a-b+1)-1})'
    else:
      mask = f'(v & ({2**(a-b+1)-1}<<{b}))'
    if shift == 0:
      ret += mask
    elif shift > 0:
      ret += f'({mask} << {shift})'
    else:
      ret += f'({mask} >> {-shift})'
  ret += '; }'
  return ret

def main():
  tbl = [
    '3',
    '3:1',
    '3:1|9:8',
    '5|z3|2',
  ]
  for ptn in tbl:
    print(bitPattern(ptn))

if __name__ == '__main__':
  main()
