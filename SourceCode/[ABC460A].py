a, b = map(int, input().split())

cnt = 0
while(b):
    b = a % b
    cnt += 1
    
print(cnt)