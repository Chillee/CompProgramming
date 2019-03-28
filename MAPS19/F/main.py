import math
import decimal
from decimal import *
T = int(input())


def pi():
    """Compute Pi to the current precision.

    >>> print(pi())
    3.141592653589793238462643383

    """
    getcontext().prec += 2  # extra digits for intermediate steps
    three = Decimal(3)      # substitute "three=3.0" for regular floats
    lasts, t, s, n, na, d, da = 0, three, 3, 1, 0, 0, 24
    while s != lasts:
        lasts = s
        n, na = n+na, na+8
        d, da = d+da, da+32
        t = (t * n) / d
        s += t
    getcontext().prec -= 2
    return +s               # unary plus applies the new precision


getcontext().prec = 50
for _ in range(T):
    R, N = input().split()
    R, N = Decimal(int(R)), Decimal(int(N))
    f = pi()
    s = pi()/4
    s *= Decimal(1.75)**(N-2)
    if (N == 1):
        print(f*R*R)
    else:
        print((f+4*s)*R*R)
