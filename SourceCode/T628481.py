#
#   @ Author:       Eric / Sky__White
#   @ Filename:     T628481.py
#   @ Time:         12/31/2025
#   @ Email:        acwing@foxmail.com
#

n, m = map(int, input().split())

arr = list(map(int, input().split()))

l = int(max(arr))

res = 0

for i in arr:
    res = max((l - i + m - 1) // m, res)
    
print(res)