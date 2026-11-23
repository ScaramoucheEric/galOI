#
#   @ Author:       Eric / Sky__White
#   @ Filename:     [ABC446B].py
#   @ Time:         02/21/2026
#   @ Email:        acwing@foxmail.com
#

n, m = map(int, input().split())

x = []

for i in range(n):
    nn = int(input())
    
    arr = list(map(int, input().split()))
    x.append(arr)

st = []
cnt = [0 for _ in range(n)]

for i in range(n):
    for j in x[i]:
        if (j not in st):
            st.append(j)
            cnt[i] = j
            break
            
            
for i in range(n):
    print(cnt[i])