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
bool isPrime(ull p) {
    if (p == 2)
        return true;
    if (p == 1 || p % 2 == 0)
        return false;
    ull s = p - 1;
    while (s % 2 == 0)
        s /= 2;
    for (ull i = 0; i < 15; ++i) {
        ull a = rand() % (p - 1) + 1, tmp = s;
        ull mod = binExp(a, s, p);
        while (tmp != p - 1 && mod != 1 && mod != p - 1) {
            mod = binExp(mod, 2, p);
            tmp *= 2;
        }
        if (mod != p - 1 && tmp % 2 == 0)
            return false;
    }
    return true;
}
#define all(x) x.begin(), x.end()
bool isPrime2(ull n) {
    vector<ull> ps({2, 3, 5, 13, 19, 73, 193, 407521, 299210837});
    vector<ull> cs({2, 325, 9375, 28178, 450775, 9780504, 1795265022});
    if (n <= 1 || any_of(all(ps), [&](ull p) { return n % p == 0; }))
        return count(all(ps), n) > 0;
    ull d = n - 1, s = 0;
    while (!(d & 1))
        d >>= 1, s++;
    return !any_of(all(cs), [&](ull a) {
        for (ull i = 0, p = binExp(a, d, n); i < s; i++, p = binExp(p, 2, n))
            if (p == n - 1 || (i == 0 && p == 1))
                return false;
        return true;
    });
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
    cout << isPrime2(162401) << ' ' << isPrime(162401) << endl;
    // return 0;
    vector<ull> primes, primes2;
    const ull start = 0, uller = 1e6;
    clock_t begin;
    begin = clock();
    for (ull i = start; i < start + uller; i++)
        if (isPrime(i))
            primes.push_back(i);
    cout << "kactl: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << primes.size() << endl;
    begin = clock();
    for (ull i = start; i < start + uller; i++)
        if (isPrime2(i))
            primes2.push_back(i);
    cout << "horse: " << (double)(clock() - begin) / CLOCKS_PER_SEC << ' ' << primes2.size() << endl;
    for (ull i = 0; i < 78500; i++) {
        // cout << primes[i] << ' ' << primes2[i] << endl;
        if (primes[i] != primes2[i]) {
            cout << primes[i] << ' ' << primes2[i] << endl;
            return 0;
        }
    }
}