#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
struct timeit {
    decltype(chrono::high_resolution_clock::now()) begin;
    const string label;
    timeit(string label = "???") : label(label) { begin = chrono::high_resolution_clock::now(); }
    ~timeit() {
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
        cout << duration << "ms elapsed [" << label << "]" << endl;
    }
};
mt19937_64 uni(time(0));
namespace sixtyfournonasm {
struct H {
    ull x;
    H(ull x = 0) : x(x) {}
    ull get() const { return x + !~x; }
    H operator+(H o) { return x + o.x + (x + o.x < x); }
    H operator*(H o) {
        ull a = x >> 32, b = x & -1u, c = o.x >> 32, d = o.x & -1u;
        ull y = (H(a * d) + H(b * c)).get();
        return H(a * c) + b * d + ((y & -1u) << 32 | y >> 32);
    }
    H operator-(H o) { return *this + ~o.x; }
    bool operator==(H o) const { return get() == o.get(); }
    bool operator<(H o) const { return get() < o.get(); }
};
} // namespace sixtyfournonasm

// namespace sixtyfourasm {
// struct H {
//     ull x;
//     H(ull x = 0) : x(x) {}
//     ull get() const { return x + !~x; }
//     H operator+(H o) { return x + o.x + (x + o.x < x); }
//     H operator*(H o) {
//         ull r = x;
//         asm("mul %1\n addq %%rdx, %0\n adcq $0,%0" : "+a"(r) : "r"(o.x) : "rdx");
//         return r;
//     }
//     H operator-(H o) { return *this + ~o.x; }
//     bool operator==(H o) const { return get() == o.get(); }
//     bool operator<(H o) const { return get() < o.get(); }
// };
// } // namespace sixtyfourasm

namespace dacinsixtyone {
struct H {
    ull x;
    H(ull x = 0) : x(x) {}
    ull get() const { return x + !~x; }
    const static ull M = (1ull << 61) - 1;
    H operator+(H o) {
        o.x += x + 1;
        o.x = (o.x & M) + (o.x >> 61);
        return o.x - 1;
    }
    H operator*(H o) {
        ull l1 = x & -1u, h1 = x >> 32, l2 = o.x & -1u, h2 = o.x >> 32;
        ull l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
        ull ret = (l & M) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
        ret = (ret & M) + (ret >> 61);
        ret = (ret & M) + (ret >> 61);
        return ret - 1;
    }
    H operator-(H o) { return *this + ~o.x; }
    bool operator==(H o) const { return get() == o.get(); }
    bool operator<(H o) const { return get() < o.get(); }
};
} // namespace dacinsixtyone

namespace mod1e9 {
typedef long long ll;
struct H {
    ll x;
    H(ll x = 0) : x(x) {}
    ll get() const { return x; }
    const static ll M = 1e9 + 7;
    H operator+(H o) { return o.x + x > M ? o.x + x - M : o.x + x; }
    H operator*(H o) { return x * o.x % M; }
    H operator-(H o) { return *this - o.x < 0 ? *this + M - o.x : *this - o.x; }
    bool operator==(H o) const { return get() == o.get(); }
    bool operator<(H o) const { return get() < o.get(); }
};
} // namespace mod1e9

namespace extensible {
template <class h> struct H : array<h, 2> {
    H g() { return *this; }
    H() { *this = {0, 0}; }
    H(h a) { *this = {a, a}; }
    H(h a, h b) { (*this)[0] = a, (*this)[1] = b; }
#define op(o) \
    H operator o(H a) { return {g()[0] o a[0], g()[1] o a[1]}; }
    op(+) op(-) op(*);
    H operator+(int a) { return g() + H(a); }
};
} // namespace extensible
const int MAXITERS = 5e7;
template <class H>
void benchSeq(
    string name, function<void(H)> f = [](H x) { cerr << x.get() << endl; }) {
    timeit x(name + " seq");
    H h = H(1), v = H(uni());
    for (int i = 0; i < MAXITERS; i++) {
        h = h * v + 5;
    }
    f(h);
}
template <class H>
void benchParallel(
    string name, function<void(H)> f = [](H x) { cerr << x.get() << endl; }) {
    const int NUMPAR = 4;
    timeit x(name + " parallel");
    H v = H(uni());
    vector<H> hs(NUMPAR);
    for (int i = 0; i < hs.size(); i++)
        hs[i] = H(i + 1);
    for (int i = 0; i < MAXITERS / NUMPAR; i++) {
        for (int j = 0; j < NUMPAR; j++)
            hs[j] = hs[j] * v + 5;
    }
    H sm = H(1);
    for (auto j : hs)
        sm = sm + j;
    f(sm);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    benchSeq<sixtyfournonasm::H>("2^64 non-asm");
    benchParallel<sixtyfournonasm::H>("2^64 non-asm");
    cout << endl;

    // benchSeq<sixtyfourasm::H>("2^64 non-asm");
    // benchParallel<sixtyfourasm::H>("2^64 non-asm");
    // cout << endl;

    benchSeq<ull>("64 overflow", [](auto x) { cerr << x << endl; });
    benchParallel<ull>("64 overflow", [](auto x) { cerr << x << endl; });
    cout << endl;

    benchSeq<dacinsixtyone::H>("2^61 dacin", [](auto x) { cerr << x.get() << endl; });
    benchParallel<dacinsixtyone::H>("2^61 dacin", [](auto x) { cerr << x.get() << endl; });
    cout << endl;

    benchSeq<mod1e9::H>("mod1e9", [](auto x) { cerr << x.get() << endl; });
    benchParallel<mod1e9::H>("mod1e9", [](auto x) { cerr << x.get() << endl; });
    cout << endl;

    benchSeq<extensible::H<mod1e9::H>>("double mod1e9", [](auto x) { cerr << x[0].get() << endl; });
    benchParallel<extensible::H<mod1e9::H>>("double mod1e9", [](auto x) { cerr << x[0].get() << endl; });
    cout << endl;

    // benchSeq<extensible::H<sixtyfournonasm::H>>("double 2^64 non-asm", [](auto x) { cerr << x[0].get() << endl; });
    // benchParallel<extensible::H<sixtyfournonasm::H>>("double 2^64 non-asm", [](auto x) { cerr << x[0].get() << endl; });
    // cout << endl;

    // benchSeq<extensible::H<sixtyfourasm::H>>("double 2^64 asm", [](auto x) { cerr << x[0].get() << endl; });
    // benchParallel<extensible::H<sixtyfourasm::H>>("double 2^64 asm", [](auto x) { cerr << x[0].get() << endl; });
    // cout << endl;

    // benchSeq<extensible::H<ull>>("double 64 overflow asm", [](auto x) { cerr << x[0] << endl; });
    // benchParallel<extensible::H<ull>>("double 64 overflow asm", [](auto x) { cerr << x[0] << endl; });
    // cout << endl;
}