#
#   @ Author:       Eric / Sky__White
#   @ Filename:     [ABC429B].py
#   @ Time:         10/25/2025
#   @ Email:        acwing@foxmail.com
#

n, m = map(int,input().split())

arr = list(map(int, input().split()))

Sum = sum(arr)

for i in arr:
    if (Sum - i == m):
        print("Yes")
        exit(0)
        
print("No")