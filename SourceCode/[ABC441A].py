#
#   @ Author:       Eric / Sky__White
#   @ Filename:     [ABC441A].py
#   @ Time:         01/17/2026
#   @ Email:        acwing@foxmail.com
#

n, m = map(int, input().split())
x, y = map(int, input().split())

if (x - n >= 0 and x - n < 100 and y - m >= 0 and y - m < 100):
    print("Yes")
else:
    print("No")