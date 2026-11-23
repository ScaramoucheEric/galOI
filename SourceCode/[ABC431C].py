#
#   @ Author:       Eric / Sky__White
#   @ Filename:     [ABC431C].py
#   @ Time:         11/08/2025
#   @ Email:        acwing@foxmail.com
#

n, m, k = map(int,input().split())

h = list(map(int,input().split()))
b = list(map(int,input().split()))

h.sort()
b.sort()

pos1, pos2, cnt = 0, 0, 0

# print(h, b, sep = '\n')

while(pos1 < n and pos2 < m):
    if (h[pos1] > b[pos2]):
        pos2 += 1
    else:
        cnt += 1
        pos1 += 1
        pos2 += 1
    # print(cnt)
        
print("Yes") if (cnt >= k) else print("No")