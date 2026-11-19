n, m = map(int, input().split())
iland = []

for i in range(n):
    iland.append(list(map(int,input().split())))

arr = list(map(int,input().split()))
print("arr:", arr)
for i in range(m):
    arr[i] = [arr[i], i + 1]

arr.sort()

print("arr:", arr)

bri = []

for i in range(0, n - 1):
    bri.append([iland[i + 1][0] - iland[i][1], iland[i + 1][1] - iland[i][0], i + 1])
    
bri.sort()

print("bri:", bri)

pos = 1
res = dict()
pos -= 1

for [l, r, opt] in bri:
    while(pos < m and (arr[pos][0] < l or arr[pos][0] > r)) : pos += 1
    if (pos >= m):
        print("No")
        exit(0)
    elif (arr[pos][0] >= l and arr[pos][0] <= r):
        print(l, r)
        print(arr[pos][0], arr[pos][1])
        print(opt, pos, arr[pos][1], arr[pos][0])
        res[opt] = arr[pos][1]
    pos += 1
    print()
        
print("Yes")

for i in range(1, n):
    print(res[i], end = ' ')
    
#
#
# 5 9
# 1 2
# 3 3
# 5 7
# 11 13
# 14 20
# 2 3 4 10 6 2 6 9 5
