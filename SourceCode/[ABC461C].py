N, K, M = map(int, input().split())

arr = [[] for i in range(N + 1)]

for i in range(N):
    c, v = map(int, input().split())

    arr[c].append(v)

m = 0

for i in range(N + 1):
    arr[i].sort()
    arr[i].reverse()
    # print(arr[i])

arr.sort()
arr.reverse()

for i in range(M):
    m += arr[i][0]
    arr[i].remove(arr[i][0])
    # print(arr[i])

li = []

for i in arr:
    for j in i:
        li.append(j)

li.sort()
li.reverse()

K -= M

for i in range(K):
    m += li[i]

print(m)