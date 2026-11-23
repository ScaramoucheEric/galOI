n, x = map(int,input().split())

arr = list(map(int, input().split()))

for i in arr:
    if (i < x):
        x = i
        print(1)
    else:
        print(0)