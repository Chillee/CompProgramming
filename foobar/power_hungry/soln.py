def answer(xs):
    zeros = [i for i in xs if i==0]
    pos = [i for i in xs if i > 0]
    neg = sorted([abs(i) for i in xs if i < 0])
    if len(pos) + len(neg) == 0:
        return 0
    if len(zeros) > 1 and len(neg) == 1:
        return 0
    if len(neg) == 1 and len(pos) == 0 and len(zeros) == 0:
        return neg[0]
    res = 1
    for i in pos:
        res *= i
    if len(neg)%2 == 0:
        for i in neg:
            res *= i
    else:
        for i in neg[1:]:
            res *= i
    return str(res)

print(answer([-1]))