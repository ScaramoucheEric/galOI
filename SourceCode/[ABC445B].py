s = []

n = int(input())

sz = 0

for i in range(n):
  s.append(input())
  sz = max(sz, len(s[i]))
  
for i in range(n):
  k = sz - len(s[i])
  k //= 2
  print('.' * k + s[i] + '.' * k)
  