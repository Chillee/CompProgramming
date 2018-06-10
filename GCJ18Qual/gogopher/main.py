T = int(input())

for _ in range(T):
    A = int(input())
    squares = set()
    l = r = d = u = None
    if A == 20:
        l, r, d, u = 10, 15, 10, 14
    else:
        l, r, d, u = 10, 25, 10, 24

    for i in range(l, r):
        for j in range(d, u):
            squares.add((i, j))
    while len(squares):
        cur = next(iter(squares))
        curx, cury = cur
        curx = max(curx, l+1)
        curx = min(curx, r-2)
        cury = max(cury, d+1)
        cury = min(cury, u-2)
        print(str(curx)+" "+str(cury))
        res = input().split(' ')
        resx, resy = res
        resx = int(resx)
        resy = int(resy)
        if resx == 0 and resy == 0:
            break
        res = (resx, resy)
        if res in squares:
            squares.remove(res)
