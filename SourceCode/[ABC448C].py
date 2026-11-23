N, Q = map(int, input().split())
A = list(map(int, input().split()))

balls = [(A[i], i + 1) for i in range(N)]
balls.sort()

scnt = min(6, N)
cball = balls[:scnt]

for _ in range(Q):
    K = int(input())
    un = set(map(int, input().split()))
    
    for val, idx in cball:
        if idx not in un:
            print(val)
            break
