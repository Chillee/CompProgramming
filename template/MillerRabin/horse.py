def is_prime(n):
    """ Deterministic variant of the Miller-Rabin primality test. """
    if n in [2, 3, 5, 13, 19, 73, 193, 407521, 299210837]:
        return True

    if (n in [0, 1]) or (any(n % p == 0 for p in [2, 3, 5, 13, 19, 73, 193, 407521, 299210837])):
        return False

    d, s = n - 1, 0
    while d & 1 == 0:
        d, s = d >> 1, s + 1

    def try_composite(a):
        if pow(a, d, n) == 1:
            return False
        for i in range(s):
            if pow(a, 2**i * d, n) == n - 1:
                return False
        return True

    return not any(try_composite(w) for w in [2, 325, 9375, 28178, 450775, 9780504, 1795265022])


p = (1 << 61) - 1
print(is_prime(p))
