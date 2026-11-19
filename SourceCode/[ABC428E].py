from collections import deque
import sys

def wznork():
    input = sys.stdin.read
    data = input().split()
    n = int(data[0])
    graph = [[] for _ in range(n + 1)]
    idx = 1
    for _ in range(n - 1):
        a = int(data[idx]); idx += 1
        b = int(data[idx]); idx += 1
        graph[a].append(b)
        graph[b].append(a)
    
    def farthest(start):
        dist = [-1] * (n + 1)
        dist[start] = 0
        q = deque([start])
        while q:
            u = q.popleft()
            for v in graph[u]:
                if dist[v] == -1:
                    dist[v] = dist[u] + 1
                    q.append(v)
        max_dist = -1
        node = -1
        for i in range(1, n + 1):
            if dist[i] > max_dist or (dist[i] == max_dist and i > node):
                max_dist = dist[i]
                node = i
        return node, dist
    
    u, _ = farthest(1)
    v, dist_u = farthest(u)
    _, dist_v = farthest(v)
    
    res = []
    for i in range(1, n + 1):
        if dist_u[i] > dist_v[i]:
            res.append(u)
        elif dist_u[i] < dist_v[i]:
            res.append(v)
        else:
            res.append(max(u, v))
    
    print("\n".join(map(str, res)))

if __name__ == "__main__":
    wznork()