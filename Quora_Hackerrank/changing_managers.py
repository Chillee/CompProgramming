N = int(input())
L = []
E = []
for i in range(N):
    l, e = input().split()
    l = int(l)
    e = int(e)
    L.append(l)
    E.append(e)

sorted_L = sorted([(b, a) for a, b in enumerate(list(L))])
sorted_E = sorted(E)
for v, idx in sorted_L:

