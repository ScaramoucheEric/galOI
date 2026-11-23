n = int(input())

k = []
arr = [[] for _ in range(n + 1)]

for i in range(1, n + 1):
    l = list(map(int, input().split()))

    for j in l[1:]:
        arr[j].append(i)

for i in range(1, n + 1):
    print(len(arr[i]), end = ' ')
    for j in arr[i]:
        print(j, end = ' ')
    print()