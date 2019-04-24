def f(a, b):
    vals = set([a])
    c = a*a % b
    while c != 1 and c != 0 and c != a:
        vals.add(c)
        c = c*a % b
        print(c)
    vals.add(c)
    print(c)
    return vals


res = f(6, 7)
print(res)
print(len(res))
