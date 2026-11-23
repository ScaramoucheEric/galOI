def count(S):
    n = len(S)
    count = 0
    
    for i, char in enumerate(S):
        if char == 'C':
            max_k = min(i, n - 1 - i)
            count += max_k + 1
    
    return count

S = input()
print(count(S))