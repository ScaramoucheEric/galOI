#
#   @ Author:       Eric / Sky__White
#   @ Filename:     [ABC452B].py
#   @ Time:         04/04/2026
#   @ Email:        acwing@foxmail.com
#

H, W = map(int, input().split())

for i in range(H):
    row = ""
    for j in range(W):
        if i == 0 or i == H-1 or j == 0 or j == W-1:
            row += "#"
        else:
            row += "."
    print(row)