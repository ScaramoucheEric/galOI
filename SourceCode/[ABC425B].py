def solve():
    N = int(input())
    A = list(map(int, input().split()))
    
    fixed = {}
    free_slots = []
    
    for i, val in enumerate(A):
        if val != -1:
            if val in fixed:
                print("No")
                return
            fixed[val] = i
        else:
            free_slots.append(i)
    
    used_set = set(fixed.keys())
    free_numbers = [x for x in range(1, N + 1) if x not in used_set]
    
    P = [0] * N
    for idx, val in fixed.items():
        P[val] = idx
    
    for slot, num in zip(free_slots, free_numbers):
        P[slot] = num
    
    print("Yes")
    print(" ".join(map(str, P)))

if __name__ == "__main__":
    solve()