import math

def solve():
    import sys
    input = sys.stdin.read
    data = input().split()
    t = int(data[0])
    idx = 1
    res = []
    for _ in range(t):
        C = int(data[idx]); idx += 1
        D = int(data[idx]); idx += 1
        
        len_C1 = len(str(C + 1))
        len_CD = len(str(C + D))
        
        ans = 0
        for L in range(len_C1, len_CD + 1):
            base = C * (10**L)
            low1 = base + C + 1
            low2 = base + 10**(L - 1)
            high1 = base + C + D
            high2 = base + (10**L - 1)
            
            low = max(low1, low2)
            high = min(high1, high2)
            
            if low > high:
                continue
            
            m_min = math.isqrt(low - 1) + 1
            m_max = math.isqrt(high)
            
            if m_min <= m_max:
                ans += m_max - m_min + 1
        res.append(ans)
    
    print("\n".join(map(str, res)))

if __name__ == "__main__":
    solve()