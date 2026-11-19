import sys

def main():
    input = sys.stdin.read
    data = input().split()
    
    idx = 0
    N = int(data[idx]); idx += 1
    Q = int(data[idx]); idx += 1
    
    A = []
    for _ in range(N):
        A.append(int(data[idx])); idx += 1
    
    # Precompute prefix sums
    prefix = [0] * (N + 1)
    for i in range(1, N + 1):
        prefix[i] = prefix[i - 1] + A[i - 1]
    
    start = 0  # Index of the first element in the current view
    
    results = []
    
    for _ in range(Q):
        t = int(data[idx]); idx += 1
        
        if t == 1:
            c = int(data[idx]); idx += 1
            start = (start + c) % N
        else:
            l = int(data[idx]); idx += 1
            r = int(data[idx]); idx += 1
            
            # Convert to 0-based indices in the circular array
            l0 = (start + l - 1) % N
            r0 = (start + r - 1) % N
            
            if l0 <= r0:
                # Normal case: the range doesn't wrap around
                total = prefix[r0 + 1] - prefix[l0]
            else:
                # Wraparound case: the range crosses the end of the array
                total = (prefix[N] - prefix[l0]) + prefix[r0 + 1]
            
            results.append(str(total))
    
    print("\n".join(results))

if __name__ == "__main__":
    main()