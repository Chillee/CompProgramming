#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

struct H {
    const static ull M = (1ull << 61) - 1;
    ull x;
    H(ull x = 0) : x(x) {}
    ull get() const { return x; }
    H operator+(H o) { return x + o.x + (x + o.x < x); }
    // H operator+(H o) {
    //     ull v = x + o.x + 1;
    //     v = (v & M) + (v >> 61);
    //     return v - 1;
    // }
    H operator*(H o) {
        ull a = x >> 32, b = x & -1u, c = o.x >> 32, d = o.x & -1u;
        ull y = (H(a * d) + H(b * c)).get();
        return H(a * c) + b * d + ((y & -1u) << 32 | y >> 32);
    }
    // H operator*(H o) {
    //     ull l1 = x & -1u, h1 = x >> 32, l2 = o.x & -1u, h2 = o.x >> 32;
    //     ull l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
    //     ull ret = (l & M) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    //     ret = (ret & M) + (ret >> 61);
    //     ret = (ret & M) + (ret >> 61);
    //     return ret - 1;
    // }
    H operator-(H o) { return *this + (M - o.x); }
    bool operator==(H o) const { return get() == o.get(); }
    bool operator<(H o) const { return get() < o.get(); }
};
struct H2 : array<H, 2> {
    H2 &g() { return *this; }
    H2(H a = 0, H b = 0) { g()[0] = a, g()[1] = b; }
#define op(o) \
    H2 operator o(H2 a) { return H2(g()[0] o a[0], g()[1] o a[1]); }
    op(+) op(-) op(*);
    H2 operator+(int a) { return g() + H2(a, a); }
};
struct RollingHash {
    H2 p = {1, 1};
    vector<H2> ha;
    vector<H2> pw;
    RollingHash(string s) : ha(s.size() + 1), pw(ha) {
        while (__gcd(p[0].get(), -1ull) > 1)
            p[0] = rand();
        while (__gcd(p[1].get(), -1ull) > 1)
            p[1] = rand();
        pw[0] = H2(1, 1);
        for (int i = 0; i < s.size(); i++)
            ha[i + 1] = ha[i] * p + s[i], pw[i + 1] = pw[i] * p;
    }
    H2 interval(int a, int b) { // hash [a, b)
        return ha[b] - ha[a] * pw[b - a];
    }
};
mt19937_64 uni(time(0));

const int ITERS = 1e4;
const ull M = (1ull << 61) - 1;

const ull mod = (1ull << 61) - 1;
uint64_t modmul(uint64_t a, uint64_t b) {
    uint64_t l1 = (uint32_t)a, h1 = a >> 32, l2 = (uint32_t)b, h2 = b >> 32;
    uint64_t l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
    uint64_t ret = (l & mod) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    ret = (ret & mod) + (ret >> 61);
    ret = (ret & mod) + (ret >> 61);
    return ret - 1;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    H2 x(5, 5);
    __uint128_t val = 1e18;
    // cout << (ull)val * 5 % (-1) << endl;
    // cout << (H(val) * 5).get() << endl;
    // return 0;
    __uint128_t cur = 1;
    // H curH = H(1);
    ull curH = 1;
    for (int i = 0; i < ITERS; i++) {
        __uint128_t r = uni() % M;
        // cout << (ull)cur << ' ' << curH.get() << ' ' << (ull)r << endl;
        cout << (ull)cur << ' ' << curH << ' ' << (ull)r << endl;
        cur = cur * r % M;
        curH = modmul(curH, r);
        // cout << (ull)cur << ' ' << curH.get() << endl;
        cout << (ull)cur << ' ' << curH << endl;
        cout << endl;
        // assert(cur == curH.get());
        assert(cur == curH);
    }
    return 0;
    // cur = -20;
    // curH = H(-20);
    // for (int i = 0; i < ITERS; i++) {
    //     cur = (cur + 1) % M;
    //     curH = curH + 1;

    //     __uint128_t r = uni();
    //     auto a = cur * r % M;
    //     auto b = curH * r;
    //     assert(cur == curH.get());
    //     assert(a == b.get());
    // }
}