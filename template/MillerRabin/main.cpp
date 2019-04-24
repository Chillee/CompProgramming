#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
const ull bits = 10;
const ull po = 1 << bits;
ull modMul(ull a, ull b, ull &c) {
    ull x = a * (b & (po - 1)) % c;
    while ((b >>= bits) > 0) {
        a = (a << bits) % c;
        x += (a * (b & (po - 1))) % c;
    }
    return x % c;
}
ull binExp(ull b, ull pw, ull MOD) {
    if (pw == 0)
        return 1;
    return modMul(binExp(modMul(b, b, MOD), pw / 2, MOD), (pw & 1 ? b : 1), MOD);
};
bool isPrime2(ull n) {
    if (n <= 1)
        return false;
    for (ull p : {2, 3, 5, 13, 19, 73, 193, 407521, 299210837})
        if (n % p == 0)
            return (n == p);
    ull d = n - 1;
    while (!(d & 1))
        d >>= 1;
    for (ull a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
        ull p = binExp(a, d, n), i = d;
        while (p != n - 1 && i != n - 1 && p != 1)
            i <<= 1, p = binExp(p, 2, n);
        if (p != n - 1 && i != d)
            return false;
    }
    return true;
}
#define all(x) x.begin(), x.end()
// Works for up to 10^9 with normal binExp, use 64 bit binExp for higher values
bool isPrime(ull n) {
    if (n < 2 || n % 2 == 0 || n % 3 == 0)
        return n - 2 < 2;
    ull s = __builtin_ctzll(n - 1), d = n >> s; // counts trailing zeros
    for (auto a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
        ull p = binExp(a, d, n), i = s;
        while (p != 1 && p != n - 1 && a < n && i--)
            p = binExp(p, 2, n);
        if (p != n - 1 && i != s)
            return 0;
    }
    return 1;
}

// ull isPrime2(ull n) {
//     vector<ull> ps({2, 3, 5, 13, 19, 73, 193, 407521, 299210837});
//     if (count(ps.begin(), ps.end(), n))
//         return true;
//     if (n <= 1 || any_of(ps.begin(), ps.end(), [&](ull p) { return n % p == 0; }))
//         return false;
//     ull d = n - 1, s = 0;
//     while (!(d & 1))
//         d >>= 1, s++;
//     vector<ull> cs({2, 325, 9375, 28178, 450775, 9780504, 1795265022});
//     return !any_of(cs.begin(), cs.end(), [&](ull a) {
//         if (binExp(a, d, n) == 1)
//             return false;
//         ull p = binExp(a, d, n);
//         for (ull i = 0; i < s; i++, p = binExp(p, 2, n))
//             if (p == n - 1)
//                 return false;
//         return true;
//     });
// }
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    srand(time(0));
    vector<ull> primes, primes2;
    cout << isPrime(4033) << endl;
    const ull start = 0, uller = 1e6;
    clock_t begin;
    begin = clock();
    for (ull i = start; i < start + uller; i++)
        if (isPrime2(i))
            primes.push_back(i);
    cout << "old: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << primes.size() << endl;
    begin = clock();
    for (ull i = start; i < start + uller; i++)
        if (isPrime(i))
            primes2.push_back(i);
    cout << "kactl: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << primes2.size() << endl;
    for (int i = 0; i < primes2.size(); i++) {
        if (primes[i] != primes2[i]) {
            cout << primes[i] << ' ' << primes2[i] << endl;
            assert(false);
        }
    }
    primes2.clear();
}