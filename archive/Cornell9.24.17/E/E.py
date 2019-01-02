from math import sqrt
from functools import reduce

sopf = [0 for i in range(100005)]
for i in range(2, 100005):
    if sopf[i] == 0:
        for j in range(i, 100005, i):
            sopf[j] += i


kappas = {1:0}
def kappa(n):
    if n not in kappas:
        kmax = max(kappas.keys())
        for i in range(kmax + 1, n + 1):
            for j in range(1, i):
                print(j, i-j)
            print()
            kappas[i] = ((sopf[i] + sum(sopf[j] * kappas[i - j] for j in range(1, i))) // i) % (1e9 + 7)
    return int(kappas[n])

N = int(input())
print(kappa(N))
