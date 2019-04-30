#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
typedef long long ll;
using namespace std;

typedef unsigned long long ull;
const int bits = 10;
// if all numbers are less than 2^k, set bits = 64-k
const ull po = 1 << bits;
int cnt = 0;
ull mod_mul(ull a, ull b, ull c) {
    cnt++;
    ull x = a * (b & (po - 1)) % c;
    while ((b >>= bits) > 0) {
        a = (a << bits) % c;
        x += (a * (b & (po - 1))) % c;
    }
    return x % c;
}
ull mod_pow(ull a, ull b, ull mod) {
    if (b == 0)
        return 1;
    ull res = mod_pow(a, b / 2, mod);
    res = mod_mul(res, res, mod);
    if (b & 1)
        return mod_mul(res, a, mod);
    return res;
}
bool isPrime(ull n) {
    if (n < 2 || n % 6 % 4 != 1)
        return n - 2 < 2;
    ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022}, s = __builtin_ctzll(n - 1), d = n >> s;
    for (auto a : A) { // ^ count trailing zeroes
        ull p = mod_pow(a, d, n), i = s;
        while (p != 1 && p != n - 1 && a % n && i--)
            p = mod_mul(p, p, n);
        if (p != n - 1 && i != s)
            return 0;
    }
    return 1;
}
namespace kactl {
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int MAX_PR = 5'000'000;
bitset<MAX_PR> isprime;
vi eratosthenes_sieve(int lim) {
    isprime.set();
    isprime[0] = isprime[1] = 0;
    for (int i = 4; i < lim; i += 2)
        isprime[i] = 0;
    for (int i = 3; i * i < lim; i += 2)
        if (isprime[i])
            for (int j = i * i; j < lim; j += i * 2)
                isprime[j] = 0;
    vi pr;
    rep(i, 2, lim) if (isprime[i]) pr.push_back(i);
    return pr;
}

ull f(ull a, ull n, ull &has) { return (mod_mul(a, a, n) + has) % n; }

vector<ull> pr;
vector<ull> factor(ull d) {
    vector<ull> res;
    for (int i = 0; i < sz(pr) && pr[i] * pr[i] <= d; i++)
        if (d % pr[i] == 0) {
            while (d % pr[i] == 0)
                d /= pr[i];
            res.push_back(pr[i]);
        }
    // d is now a product of at most 2 primes.
    if (d > 1) {
        if (isPrime(d))
            res.push_back(d);
        else
            while (true) {
                ull has = rand() % 2321 + 47;
                ull x = 2, y = 2, c = 1;
                for (; c == 1; c = __gcd((y > x ? y - x : x - y), d)) {
                    x = f(x, d, has);
                    y = f(f(y, d, has), d, has);
                }
                if (c != d) {
                    res.push_back(c);
                    d /= c;
                    if (d != c)
                        res.push_back(d);
                    break;
                }
            }
    }
    return res;
}
void init(int bits) { // how many bits do we use?
    vi p = eratosthenes_sieve(1 << ((bits + 2) / 3));
    pr.assign(all(p));
}
} // namespace kactl

// namespace horse {
// vector<ull> pollardRho(ull n) {
//     if (n == 1)
//         return {};
//     if (isPrime(n))
//         return {n};
//     ll y = rand() % n + 1, c = rand() % n + 1, m = rand() % n + 1;
//     ll g = 1, r = 1, q = 1;
//     ll ys;
//     while (g == 1) {
//         ll x = y, k = 0;
//         for (int i = 0; i < r; i++)
//             y = (mod_mul(y, y, n) + c) % n;
//         while (k < r && g == 1) {
//             ys = y;
//             for (int i = 0; i < min(m, r - k); i++) {
//                 y = (mod_mul(y, y, n) + c) % n;
//                 q = mod_mul(q, abs(x - y), n);
//             }
//             g = __gcd(q, (ll)n);
//             k += m;
//         }
//         r *= 2;
//     }
//     if (g == n) {
//         while (true) {
//             ull ys = (mod_mul(ys, ys, n) + c) % n;
//             ull g = __gcd((ull)q, n);
//             if (g > 1)
//                 break;
//         }
//     }
//     auto resa = pollardRho(g), resb = pollardRho(n / g);
//     resa.insert(resa.end(), all(resb));
//     return resa;
// }
// vector<ull> primeFactors(ull n) {
//     vector<ull> factors;
//     for (ull p : {2, 3, 5, 13, 19, 73, 193, 407521, 299210837}) {
//         if (n % p == 0) {
//             while (n % p == 0) {
//                 n /= p;
//                 factors.push_back(p);
//             }
//         }
//     }
//     auto res = pollardRho(n);
//     factors.insert(factors.end(), all(res));
//     return factors;
// }
// } // namespace horse
namespace tank {
typedef long double ld;
ull mod_mul(ull a, ull b, ull M) {
    ll ret = a * b - M * ull(ld(a) * ld(b) / ld(M));
    return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
// ull mod_mul(ull a, ull b, ull c) {
//     asm("mul %0\ndiv %2\n" : "+d"(b) : "a"(a), "r"(c));
//     return b;
// }
ull Pollard(ull n) {
    if (!(n & 1))
        return 2;
    if (isPrime(n))
        return n;
    auto f = [&n](ull x) { return (mod_mul(x, x, n) + 1) % n; };
    for (int i = 2;; i++) {
        ull x = i, y = f(x), p = __gcd(n + y - x, n);
        while (p == 1)
            x = f(x), y = f(f(y)), p = __gcd(n + y - x, n);
        if (p != n)
            return p;
    }
}
vector<ull> factor(ull n) {
    if (n == 1)
        return {};
    ull x = Pollard(n);
    if (x == n)
        return {x};
    auto l = factor(x), r = factor(n / x);
    l.insert(l.end(), all(r));
    return l;
}

} // namespace tank
struct timeit {
    decltype(chrono::high_resolution_clock::now()) begin;
    const string label;
    timeit(string label = "???") : label(label) { begin = chrono::high_resolution_clock::now(); }
    ~timeit() {
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
        cerr << duration << "ms elapsed [" << label << "]" << endl;
    }
};
const int ITERS = 1e4;

signed main() {
    ios::sync_with_stdio(0);
    kactl::init(51);
    cin.tie(0);
    ull val = (1ull << 50);
    // auto res = tank::factor(125);
    // auto res = tank::factor(125);
    // cout << cnt << endl;
    // cout << isPrime(1) << endl;
    // return 0;
    vector<ull> test;
    for (int i = 0; i < ITERS; i++)
        test.push_back(((ull)rand() * rand() % (1ll << 50)) + 2);

    {
        timeit x("tank1");
        ull val = 0;
        for (int i = 0; i < ITERS; i++) {
            auto res = tank::factor(test[i]);
            val += *min_element(all(res));
        }
        cout << val << endl;
        cout << "cnt: " << cnt << endl;
        cnt = 0;
    }
    {
        timeit x("kactl");
        ull val = 0;
        for (int i = 0; i < ITERS; i++) {
            auto res = kactl::factor(test[i]);
            val += *min_element(all(res));
        }
        cout << val << endl;
        cout << "cnt: " << cnt << endl;
        cnt = 0;
    }
}