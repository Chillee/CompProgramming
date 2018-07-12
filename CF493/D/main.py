import operator as op
from functools import reduce


def ncr(n, r):
    r = min(r, n-r)
    numer = reduce(op.mul, range(n, n-r, -1), 1)
    denom = reduce(op.mul, range(1, r+1), 1)
    return numer//denom


N = int(input())
ans = 0
for b in range(9):
    for c in range(9):
        if b+c > N or (b >= 5 and c >= 1):
            continue
        ans += ncr(N-b-c+1, 1)


print(ans)
