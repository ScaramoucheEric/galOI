L, R, D, U = map(int, input().split())
ans = 0

def cnt(l: int, r: int):
    if l > r:
        return 0
    return r // 2 - (l - 1) // 2

for x in range(L, R + 1):
    a = abs(x)
    if a % 2 == 0:
        low1 = max(D, -a)
        high1 = min(U, a)
        cnt1 = max(0, high1 - low1 + 1)
        
        cnt2 = cnt(D, min(U, -a - 1))
        cnt3 = cnt(max(D, a + 1), U)
        
        ans += cnt1 + cnt2 + cnt3
    else:
        cnt2 = cnt(D, min(U, -a - 1))
        cnt3 = cnt(max(D, a + 1), U)
        ans += cnt2 + cnt3

print(ans)
