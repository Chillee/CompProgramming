from random import choice


def p(r, l):
    iters = int(1e5)

    succ = 0
    for _ in range(iters):
        cur = 0
        while cur > -l and cur < r:
            cur += choice([-1, 1])
        if cur == r:
            succ += 1

    return succ/iters


def p2(r, l):
    d = r-l
    l += 1
    f1d = (d//l)+1
    f2d = (d//l)+2
    wb = l-((d+1) % l)
    wa = l-wb
    print(f1d, f2d, wa, wb)
    return l/(wa*f1d + wb*f2d)


for i in range(3, 8):
    print(p(i, 2))
# print(p2(1, 1))
# print(p2(5, 2))
