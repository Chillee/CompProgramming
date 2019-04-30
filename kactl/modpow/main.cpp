#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
typedef long long ull;
using namespace std;
const int MOD = 1e9 + 7;

typedef unsigned long long ll;
typedef long double ld;
ull mod_mul(ull a, ull b, ull M) {
    ll ret = a * b - M * ull(ld(a) * ld(b) / ld(M));
    return ret + M * ((ret < 0) - (ret >= (ll)M));
}
namespace noam {
ull pw(ull b, ull e) {
    ull ans = 1;
    for (; e; b = b * b % MOD, e /= 2)
        if (e & 1)
            ans = ans * b % MOD;
    return ans;
}

} // namespace noam
namespace kactl {
ll modpow(ll a, ll e) {
    if (e == 0)
        return 1;
    ll x = modpow(a * a % MOD, e >> 1);
    return e & 1 ? x * a % MOD : x;
}
} // namespace kactl
namespace dynamickactl {
ull mod = MOD;
ull mod_pow(ull a, ull b) {
    if (b == 0)
        return 1;
    ull res = mod_pow(a, b / 2);
    res = mod_mul(res, res, mod);
    return b & 1 ? mod_mul(res, a, mod) : res;
}
} // namespace dynamickactl
namespace dynamicnoam {
ull mod = MOD;
ull pw(ull b, ull e) {
    ull ans = 1;
    for (; e; b = mod_mul(b, b, MOD), e /= 2)
        if (e & 1)
            ans = mod_mul(ans, b, MOD);
    return ans;
}
} // namespace dynamicnoam
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

template <class F> void benchmarkSeq(F f, string name) {
    timeit x(name + "seq");
    const int ITERS = 1e6;
    ull start = 3;
    for (int i = 0; i < ITERS; i++) {
        start = f(start, rand());
    }
    assert(start != 0);
}
template <class F> void benchmarkPar(F f, string name) {
    timeit x(name + "parallel");
    const int ITERS = 1e6;
    ull start = 3;
    for (int i = 0; i < ITERS; i++) {
        start += f(rand(), rand());
    }
    assert(start != 0);
    // cout << start << endl;
}
template <class F> void benchmark(F f, string name) {
    benchmarkSeq(f, name);
    benchmarkPar(f, name);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    benchmark(noam::pw, "noam");
    benchmark(kactl::modpow, "kactl");

    benchmark(dynamickactl::mod_pow, "dynamic kactl");
    benchmark(dynamicnoam::pw, "dynamic noam");
}