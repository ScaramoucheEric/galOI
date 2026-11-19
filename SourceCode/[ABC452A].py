#
#   @ Author:       Eric / Sky__White
#   @ Filename:     [ABC452A].py
#   @ Time:         04/04/2026
#   @ Email:        acwing@foxmail.com
#

a, b = map(int,input().split())

if (a == 1 and b == 7 or a == 3 and b == 3 or a == 7 and b == 7 or a == 9 and b == 9 or a == 5 and b == 5):
    print("Yes")
else:
    print("No")