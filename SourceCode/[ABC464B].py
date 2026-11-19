H, W = map(int, input().split())
grid = [list(input().strip()) for _ in range(H)]

top, bottom, left, right = H, -1, W, -1

for i in range(H):
    for j in range(W):
        if grid[i][j] == '#':
            top = min(top, i)
            bottom = max(bottom, i)
            left = min(left, j)
            right = max(right, j)

for i in range(top, bottom + 1):
    print(''.join(grid[i][left:right + 1]))