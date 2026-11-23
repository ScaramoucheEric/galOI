#
#   @ author:       Eric / sky__White
#   @ Filename:     [aBC441].py
#   @ Time:         01/17/2026
#   @ Email:        acwing@foxmail.com
#


n, k, x = map(int, input().split())
a = list(map(int, input().split()))

a.sort(reverse = True)
s = [0] * (n + 1)
for i in range(n):
    s[i + 1] = s[i] + a[i]

R = n - k

if s[n] - s[R] < x:
    print(-1)
    exit(0)

l, r = R + 1, n
while l < r:
    mid = (l + r) // 2
    if s[mid] - s[R] >= x:
        r = mid
    else:
        l = mid + 1
print(r)
