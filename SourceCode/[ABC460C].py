n, m = map(int, input().split())
A = list(map(int, input().split()))
B = list(map(int, input().split()))

A.sort()
B.sort()

i = 0
j = 0 
res = 0

while i < n and j < m:
    if B[j] <= 2 * A[i]:
        res += 1
        i += 1
        j += 1
    else:
        i += 1

print(res)