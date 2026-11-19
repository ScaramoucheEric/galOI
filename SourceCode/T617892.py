#
#   @ Author:       Eric / Sky__White
#   @ Filename:     T617892.py
#   @ Time:         12/31/2025
#   @ Email:        acwing@foxmail.com
#

def check(r, q, n, m):
    if q == 0:
        return r <= m
    k = m // 3

    tnd = (r - 1 + n - 1) // n
    if tnd > q:
        sc = q * n
        if r - 1 > sc:
            nnd = r - 1 - sc

            mab = q * k + nnd
            return mab < m
        else:
            tnd = q

    mab = tnd * k
    return mab < m

if __name__ == '__main__':
    T = int(input())
    
    for i in range(T):
        r, q, n, m = map(int, input().split())
        print("Yes" if (check(r, q, n, m)) else "No")