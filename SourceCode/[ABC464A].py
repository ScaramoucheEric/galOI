s = input()

east, west = 0, 0
for i in s:
    if (i == 'E'):
        east += 1
    else:
        west += 1

if (east > west):
    print("East")
else:
    print("West")