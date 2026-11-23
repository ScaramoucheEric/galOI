
n = int(input())
A = list(map(int, input().split()))

coins_1 = 0
coins_10 = 0
coins_100 = 0

for a in A:
    paid = ((a + 999) // 1000) * 1000
    change = paid - a
    
    c100 = change // 100
    change %= 100
    c10 = change // 10
    c1 = change % 10
    
    coins_100 += c100
    coins_10 += c10
    coins_1 += c1

print(coins_1, coins_10, coins_100)
