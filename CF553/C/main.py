MOD = int(1e9+7)


def binExp(b, pw):
    if pw == 0:
        return 1
    return binExp(b*b % MOD, int(pw//2))*(b if pw & 1 else 1) % MOD


def mod_inv(a):
    return binExp(a, MOD-2)


def sumCons(n):
    return n*(n+1)*mod_inv(2)


def modMul(a, b):
    return a*b % MOD


def sumE(l, r):
    return (modMul(sumCons(r), 2) - modMul(sumCons(l), 2) + MOD) % MOD


def sumO(l, r): return (modMul(sumCons(r), 2) -
                        r - (modMul(sumCons(l), 2) - l) + MOD) % MOD


def f(x):
    isO = True
    oCnt = 0
    eCnt = 0
    pw = 1
    val = 0
    while x > 0:
        num = min(x, pw)
        if isO:
            val += sumO(oCnt, oCnt+num)
            val %= MOD
            oCnt += num
        else:
            val += sumE(eCnt, eCnt+num)
            val %= MOD
            eCnt += num
        val += MOD
        val %= MOD
        isO = not isO
        pw *= 2
        x -= num
    return val


l, r = [int(i) for i in input().split()]
print((f(r)-f(l-1)+MOD) % MOD)
