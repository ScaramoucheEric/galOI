t = input()
a = []
for i in range(len(t)):
    a.append(t[i])
a.sort()

for i in range(len(a)):
    if (a[i] != '0'):
        pos = i
        break

# print(pos)

a[0], a[pos] = a[pos], a[0]

for i in a:
    print(i, end = '')