import sys
data = sys.stdin.read().split()
N = int(data[0])
K = int(data[1])
M = 1 << N
if K % M == 0:
    U = 0
    base = (K + M - 1) // M
    arr = [str(base)] * M
    print(U)
    print(" ".join(arr))
else:
    U = 1
    base = K // M
    r = K % M
    arr = [str(base + 1)] * r + [str(base)] * (M - r)
    print(U)
    
    print(" ".join(arr))
    