#
#   @ Author:       Eric / Sky__White
#   @ Filename:     [ABC444B].py
#   @ Time:         02/07/2026
#   @ Email:        acwing@foxmail.com
#

n, k = map(int, input().split())

cnt = 0

for i in range(1, n + 1):
    t, id = 0, i
    while(id > 0):
        t += id % 10
        id //= 10
    if (t == k): cnt += 1
    
print(cnt)