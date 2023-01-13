def bitPattern(ptn):
  """
  ptn is bit pattern
  mask(n) = (1 << n) - 1
  {a}     => 1<<a
  {a}:{b} => mask(a-b+1)<<b
  5:2|7:6 => (mask(5-2+1)<<2) concat (mask(5-6+1)<<6)
  """
  print(f'size_t get{ptn.replace("|", "_").replace(":", "to")}(size_t v) {{ return ', end='')
  v = []
  pos = 0
  for e in reversed(ptn.split('|')):
    if ':' in e:
      ab = e.split(':')
      a = int(ab[0])
      b = int(ab[1])
    else:
      a = b = int(e)
    v.append((a, b, pos))
    pos += a-b+1
  first = True
  for (a, b, pos) in reversed(v):
    if first:
      first = False
    else:
      print('| ', end='')
    shift = pos - b
    if b == 0:
      mask = f'(v & {2**(a-b+1)-1})'
    else:
      mask = f'(v & ({2**(a-b+1)-1}<<{b}))'
    if shift == 0:
      print(mask, end='')
    elif shift > 0:
      print(f'({mask} << {shift})', end='')
    else:
      print(f'({mask} >> {-shift})', end='')
  print(';}')
 
