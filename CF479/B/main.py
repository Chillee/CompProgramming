
n = int(input())
k = input()
d = {}
for i in range(len(k)-1):
    m = ''.join(k[i:i+2])
    if m in d:
        d[m] += 1
    else:
        d.update({m: 1})
m = 0
p = ''
for i in d:
    if d[i] > m:
        m = d[i]
        p = i
print(p)
