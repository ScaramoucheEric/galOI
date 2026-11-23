x = int(input())

n = int(input())

w = list(map(int,input().split()))

st = [False for _ in range(n)]

q = int(input())

while(q):
    q -= 1
    p = int(input()) - 1
    
    if (st[p]):
        x -= w[p]
    else:
        x += w[p]
        
    st[p] = not st[p]

    print(x)