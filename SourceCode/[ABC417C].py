from collections import defaultdict

def solve():
    import sys
    input = sys.stdin.read
    data = input().split()
    
    N = int(data[0])
    A = list(map(int, data[1:N+1]))
    
    counts = defaultdict(int)
    total_pairs = 0
    
    for j in range(1, N + 1):
        current_val = j - A[j - 1]
        total_pairs += counts.get(current_val, 0)
        to_store = j + A[j - 1]
        counts[to_store] += 1
    
    print(total_pairs)

solve()