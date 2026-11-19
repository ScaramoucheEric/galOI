T = int(input().strip())
for _ in range(T):
    nA, nB, nC = map(int, input().split())
    total = nA + nB + nC
    ans = min(nA, nC, total // 3)
    print(ans)