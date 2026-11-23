import bisect
import sys

data = sys.stdin.read().split()
n = int(data[0])
s = int(data[1])
L = int(data[2])
A = list(map(int, data[3:3+n-1])) if n > 1 else []

P = [0] * (n + 1)
for i in range(1, n):
    P[i+1] = P[i] + A[i-1]

ans = 1

for l in range(s, 0, -1):
    DL = P[s] - P[l]
    
    ml = P[s] + L - 2 * DL      
    mm = P[s] + (L - DL) / 2.0  
    
    r1 = s - 1
    if ml >= P[s]:
        r1 = bisect.bisect_right(P, ml, s, n+1) - 1
        
    r2 = s - 1
    if mm >= P[s]:
        r2 = bisect.bisect_right(P, mm, s, n+1) - 1
        
    r = max(r1, r2)
    if r >= s:
        ans = max(ans, r - l + 1)
        
print(ans)
