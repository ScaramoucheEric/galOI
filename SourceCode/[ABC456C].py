MOD = 998244353

def count(s):
    n = len(s)
    g = [0] * n
    g[0] = 1
    total = g[0]
    for i in range(1, n):
        if s[i] != s[i-1]:
            g[i] = g[i-1] + 1
        else:
            g[i] = 1
        total = (total + g[i]) % MOD
    return total

s = input().strip()
print(count(s))