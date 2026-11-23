N, M = map(int, input().split())

cnt = [0] * (N + 1)
cur = [0] * (N + 1)
dis = 0

events = []

for i in range(1, N + 1):
    A, D, B = map(int, input().split())
    events.append((D, i, A, B))
    cur[i] = A
    if cnt[A] == 0:
        dis += 1
    cnt[A] += 1

events.sort()

day = 1
idx = 0
ans = []

while day <= M:
    while idx < len(events) and events[idx][0] == day:
        _, bird, A, B = events[idx]

        cnt[A] -= 1
        if cnt[A] == 0:
            dis -= 1

        if cnt[B] == 0:
            dis += 1
        cnt[B] += 1

        cur[bird] = B
        idx += 1

    ans.append(str(dis))
    day += 1

print("\n".join(ans))