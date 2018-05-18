from math import floor, ceil
vals = set()
sqrts = set()
vals.add(1)
sqrts.add(1)

for i in range(3, 60):
    cur = 2
    while True:
        t = cur**i
        if t > 1e18:
            break
        vals.add(t)
        if int(t**(1/2))**2 == t:
            sqrts.add(t)
        cur += 1

vals = sorted(list(vals))
sqrts = sorted(list(sqrts))


def bin_search(val, l, r, arr):
    if l == r-1:
        return l
    mid = (l+r)//2
    if val < arr[mid]:
        return bin_search(val, l, mid, arr)
    else:
        return bin_search(val, mid, r, arr)


Q = int(input())

for _ in range(Q):
    t = input().split()
    L, R = t
    L = int(L)
    R = int(R)
    res = 0
    lower = L**(1/2)
    upper = R**(1/2)
    # print("lower/upper: ", lower, upper)
    res += floor(upper)-ceil(lower) + 1
    uidx = bin_search(R, 0, len(sqrts), sqrts)
    lidx = bin_search(L, 0, len(sqrts), sqrts)
    res -= uidx - lidx
    uidx = bin_search(R, 0, len(vals), vals)
    lidx = bin_search(L, 0, len(vals), vals)
    res += uidx - lidx
    print(res)
