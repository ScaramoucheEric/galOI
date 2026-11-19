#
#   @ Author:       Eric / Sky__White
#   @ Filename:     [ABC453C].py
#   @ Time:         04/04/2026
#   @ Email:        acwing@foxmail.com
#

N = int(input())
A = []
B = []
for _ in range(N):
    a, b = map(int, input().split())
    A.append(a)
    B.append(b)

M = int(input())
ss = [input() for _ in range(M)]


possible = [[[False] * 26 for _ in range(11)] for _ in range(11)]

for s in ss:
    L = len(s)
    for p in range(1, L+1):
        c = ord(s[p-1]) - ord('a')
        possible[L][p][c] = True


for s in ss:  
    ok = True
    for i in range(N):
        L = A[i]
        p = B[i]
        c = s[i]
        if L > 10 or p > L:  
            ok = False
            print(ok)
            break
        if not possible[L][p][ord(c)-ord('a')]:
            ok = False
            print(ok)
            break
    print("Yes" if ok else "No")
