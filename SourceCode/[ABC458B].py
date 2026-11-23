n, m = map(int, input().split())

arr = [[[0] for _ in range(m)] for i in range(n)]

for i in range(n):
    for j in range(m):
        arr[i][j] = 4
        if (i == 0): arr[i][j] -= 1
        if (i == n - 1): arr[i][j] -= 1
        if (j == 0): arr[i][j] -= 1
        if (j == m - 1): arr[i][j] -= 1

for i in range(n):
    for j in range(m):
        print(arr[i][j], end = ' ')
    print()

