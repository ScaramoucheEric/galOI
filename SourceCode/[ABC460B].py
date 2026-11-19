import math

T = int(input())
for _ in range(T):
    X1, Y1, R1, X2, Y2, R2 = map(int, input().split())
    
    dx = X1 - X2
    dy = Y1 - Y2
    dist_sq = dx * dx + dy * dy
    
    sum_r = R1 + R2
    sum_sq = sum_r * sum_r
    diff_r = abs(R1 - R2)
    diff_sq = diff_r * diff_r
    
    if diff_sq <= dist_sq <= sum_sq:
        print("Yes")
    else:
        print("No") 