bool isPrime(ull n) { // Works for up to 10^9 with normal binExp, use 64 bit binExp for higher values
    vector<ull> ps({2, 3, 5, 13, 19, 73, 193, 407521, 299210837});
    vector<ull> cs({2, 325, 9375, 28178, 450775, 9780504, 1795265022});
    if (n <= 1 || any_of(ps.begin(), ps.end(), [&](ull p) { return n % p == 0; }))
        return (count(ps.begin(), ps.end(), n) > 0);
    ull d = n - 1, s = 0;
    while (!(d & 1))
        d >>= 1, s++;
    return !any_of(cs.begin(), cs.end(), [&](ull a) {
        for (ull i = 0, p = binExp(a, d, n); i < s; i++, p = binExp(p, 2, n))
            if (p == n - 1 || p == 1)
                return false;
        return true;
    });
}