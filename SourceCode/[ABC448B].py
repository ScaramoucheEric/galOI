n, m = map(int, input().split())

C = list(map(int, input().split()))
C.insert(0, 0)

cnt = 0

for i in range(n):
    a, b = map(int,input().split())
    if (C[a] > 0):
        if (C[a] >= b):
            cnt += b
            C[a] -= b
        else:
            cnt += C[a]
            C[a] = 0
            
print(cnt)