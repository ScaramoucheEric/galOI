a, b = map(int, input().split())

for i in range(1, a + 1):
    if (i <= b) : print("OK")
    else : print("Too Many Requests")