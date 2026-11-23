n, k = map(int, input().split())

res = n * (n - 1) // 2

k = k + res 

# print(k)

l, r = 0, 100000000

# opt = 1000
while(l < r):
  mid = (l + r) // 2
  if (mid * (mid + 1) / 2 >= k) : r = mid
  else : l = mid + 1
#   print(mid * (mid + 1) // 2, k)
#   opt -= 1
  
  
print(r - n)