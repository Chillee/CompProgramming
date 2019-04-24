#pragma GCC optimize("O2")
#include <bits/stdc++.h>

using namespace std;
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define sz(x) (int)(x).size()
typedef long long ll;

const ll MOD = (119 << 23) + 1;
namespace newkactl {
typedef vector<int> vi;
typedef vector<ll> vl;

const ll mod = (119 << 23) + 1, root = 3; // = 998244353
ll modpow(ll a, ll e) {
    if (e == 0)
        return 1;
    ll x = modpow(a * a % mod, e >> 1);
    return e & 1 ? x * a % mod : x;
}
void ntt(vl &a, vl &rt, vl &rev, int n) {
    rep(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k)
            rep(j, 0, k) {
                ll z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
                a[i + j + k] = z > ai ? ai - z + mod : ai - z;
                ai += ai + z >= mod ? z - mod : z;
            }
}

vl conv(const vl &a, const vl &b) {
    if (a.empty() || b.empty())
        return {};
    int s = sz(a) + sz(b) - 1, L = 32 - __builtin_clz(s), n = 1 << L;
    vl inl(a), inr(b), out(n), rt(n, 1), rev(n);
    inl.resize(n), inr.resize(n);
    rep(i, 0, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    int curL = mod / 2;
    for (int k = 2; k < n; k *= 2) {
        ll z[] = {1, modpow(root, curL /= 2)};
        rep(i, k, 2 * k) rt[i] = rt[i / 2] * z[i & 1] % mod;
    }
    ntt(inl, rt, rev, n), ntt(inr, rt, rev, n);
    ll invN = modpow(n, mod - 2);
    rep(i, 0, n) out[-i & (n - 1)] = (inl[i] * inr[i] % mod) * invN % mod;
    ntt(out, rt, rev, n);
    return {out.begin(), out.begin() + s};
}
} // namespace newkactl
namespace regkactl {
const ll mod = (119 << 23) + 1, root = 3; // = 998244353
// For p < 2^30 there is also e.g. (5 << 25, 3), (7 << 26, 3),
// (479 << 21, 3) and (483 << 21, 5). The last two are > 10^9.
ll modpow(ll a, ll e) {
    if (e == 0)
        return 1;
    ll x = modpow(a * a % mod, e >> 1);
    return e & 1 ? x * a % mod : x;
}
ll sub(ll a, ll b) { return (a - b) % mod; }
ll add(ll a, ll b) { return (a + b) % mod; }
// ll sub(ll a, ll b) { return b > a ? a - b + mod : a - b; }
// ll add(ll a, ll b) { return a + b >= mod ? a + b - mod : a + b; }

typedef vector<ll> vl;
void ntt(vl &a, vl &rt, vl &rev, int n) {
    rep(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k)
            rep(j, 0, k) {
                ll z = rt[j + k] * a[i + j + k] % mod;
                a[i + j + k] = sub(a[i + j], z);
                a[i + j] = add(a[i + j], z);
            }
}

vl conv(const vl &a, const vl &b) {
    if (a.empty() || b.empty())
        return {};
    int s = sz(a) + sz(b) - 1, L = 32 - __builtin_clz(s), n = 1 << L;
    vl inl(a), inr(b), out(n), rt(n, 1), rev(n);
    inl.resize(n), inr.resize(n);
    rep(i, 0, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    int curL = (mod - 1) / 2;
    for (int k = 2; k < n; k *= 2) {
        ll z[] = {1, modpow(root, curL /= 2)};
        rep(i, k, 2 * k) rt[i] = rt[i / 2] * z[i & 1] % mod;
    }
    ntt(inl, rt, rev, n), ntt(inr, rt, rev, n);
    ll invN = modpow(n, mod - 2);
    rep(i, 0, n) out[-i & (n - 1)] = (inl[i] * inr[i] % mod) * invN % mod;
    ntt(out, rt, rev, n);
    return {out.begin(), out.begin() + s};
}

} // namespace regkactl
namespace mine {
template <ll maxn> struct NTT {
    constexpr static ll lg2(ll n) { return 32 - __builtin_clz(n - 1); }
    const static ll MAXN = 1 << lg2(maxn), MOD = 998244353, root = 3;
    ll rev[MAXN], rt[MAXN];

    ll mul(ll a, ll b) { return (long long)a * b % MOD; }
    ll sub(ll a, ll b) { return b > a ? a - b + MOD : a - b; }
    ll add(ll a, ll b) { return a + b >= MOD ? a + b - MOD : a + b; }

    ll binExp(ll base, long long exp) {
        if (exp == 0)
            return 1;
        return mul(binExp(mul(base, base), exp / 2), exp & 1 ? base : 1);
    }
    NTT() {
        rt[1] = 1;
        for (ll k = 1; k < lg2(MAXN); k++) {
            ll z[] = {1, binExp(root, (MOD - 1) >> (k + 1))};
            for (ll i = (1 << k); i < 2 << k; i++)
                rt[i] = mul(rt[i / 2], z[i & 1]);
        }
    }
    void ntt(ll *a, ll n) {
        for (ll i = 0; i < n; i++)
            rev[i] = (rev[i / 2] | (i & 1) << lg2(n)) / 2;
        for (ll i = 0; i < n; i++)
            if (i < rev[i])
                swap(a[i], a[rev[i]]);
        for (ll k = 1; k < n; k *= 2) {
            for (ll i = 0; i < n; i += 2 * k)
                for (ll j = 0; j < k; j++) {
                    ll z = mul(rt[j + k], a[i + j + k]);
                    a[i + j + k] = sub(a[i + j], z);
                    a[i + j] = add(a[i + j], z);
                }
            // for (int i = 0; i < n; i++)
            //     a[i] = a[i] % MOD;
        }
    }
    ll in[2][MAXN];
    vector<ll> multiply(const vector<ll> &a, const vector<ll> &b) {
        fill(all(in[0]), 0), fill(all(in[1]), 0);
        if (a.empty() || b.empty())
            return {};
        ll sz = a.size() + b.size() - 1, n = 1 << lg2(sz);
        copy(all(a), in[0]), copy(all(b), in[1]);
        ntt(in[0], n), ntt(in[1], n);
        ll invN = binExp(n, MOD - 2);
        for (ll i = 0; i < n; i++)
            in[0][i] = mul(mul(in[0][i], in[1][i]), invN);
        reverse(in[0] + 1, in[0] + n);
        ntt(in[0], n);
        return vector<ll>(in[0], in[0] + sz);
    }
};
} // namespace mine
namespace oldkactl {
const static ll MOD = (119 << 23) + 1, root = 3; // = 998244353
ll binExp(ll base, ll exp) {
    if (exp == 0)
        return 1;
    return binExp(base * base % MOD, exp / 2) * (exp % 2 == 1 ? base : 1) % MOD;
}
void ntt(ll *x, ll *temp, ll *roots, int N, int skip) {
    if (N == 1)
        return;
    int n2 = N / 2;
    ntt(x, temp, roots, n2, skip * 2);
    ntt(x + skip, temp, roots, n2, skip * 2);
    for (int i = 0; i < N; i++)
        temp[i] = x[i * skip];
    for (int i = 0; i < n2; i++) {
        ll s = temp[2 * i], t = temp[2 * i + 1] * roots[skip * i];
        x[skip * i] = (s + t) % MOD;
        x[skip * (i + n2)] = (s - t) % MOD;
    }
}
void ntt(vector<ll> &x, bool inv = false) {
    ll e = binExp(root, (MOD - 1) / x.size());
    if (inv)
        e = binExp(e, MOD - 2);
    vector<ll> roots(x.size(), 1), temp = roots;
    for (int i = 1; i < x.size(); i++)
        roots[i] = roots[i - 1] * e % MOD;
    ntt(&x[0], &temp[0], &roots[0], x.size(), 1);
}
vector<ll> conv(vector<ll> a, vector<ll> b) {
    int s = a.size() + b.size() - 1;
    if (s <= 0)
        return {};
    int L = s > 1 ? 32 - __builtin_clz(s - 1) : 0, n = 1 << L;
    if (s <= 200) {
        vector<ll> c(s);
        for (int i = 0; i < a.size(); i++)
            for (int j = 0; j < b.size(); j++)
                c[i + j] = (c[i + j] + a[i] * b[j]) % MOD;
        return c;
    }
    a.resize(n);
    ntt(a);
    b.resize(n);
    ntt(b);
    ll d = binExp(n, MOD - 2);
    for (int i = 0; i < n; i++)
        a[i] = a[i] * b[i] % MOD * d % MOD;
    ntt(a, true);
    a.resize(s);
    for (auto &i : a)
        i = i < 0 ? i + MOD : i;
    return a;
}
} // namespace oldkactl
namespace FFTMod {
template <int maxn, int MOD> struct FFTMod {
    constexpr static int lg2(int n) { return 32 - __builtin_clz(n - 1); }
    const static int MAXN = 1 << lg2(maxn);
    typedef complex<double> cpx;
    int rev[MAXN];
    cpx rt[MAXN];
    FFTMod() {
        rt[1] = cpx{1, 0};
        for (int k = 2; k < MAXN; k *= 2) {
            cpx z[] = {1, polar(1.0, M_PI / k)};
            for (int i = k; i < 2 * k; i++)
                rt[i] = rt[i / 2] * z[i & 1];
        }
    }
    void fft(cpx *a, int n) {
        for (int i = 0; i < n; i++)
            rev[i] = (rev[i / 2] | (i & 1) << lg2(n)) / 2;
        for (int i = 0; i < n; i++)
            if (i < rev[i])
                swap(a[i], a[rev[i]]);
        for (int k = 1; k < n; k *= 2)
            for (int i = 0; i < n; i += 2 * k)
                for (int j = 0; j < k; j++) {
                    auto x = (double *)&rt[j + k], y = (double *)&a[i + j + k];
                    cpx z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);
                    a[i + j + k] = a[i + j] - z;
                    a[i + j] += z;
                }
    }

    cpx in[2][MAXN], out[2][MAXN];
    vector<ll> multiply(const vector<int> &a, const vector<int> &b) {
        fill(all(in[0]), cpx{0, 0}), fill(all(in[1]), cpx{0, 0});
        int cut = sqrt(MOD), sz = a.size() + b.size() - 1;
        int n = 1 << lg2(sz);
        vector<ll> res(sz);
        for (int i = 0; i < a.size(); i++)
            in[0][i] = {a[i] / cut, a[i] % cut};
        for (int i = 0; i < b.size(); i++)
            in[1][i] = {b[i] / cut, b[i] % cut};
        fft(in[0], n), fft(in[1], n);
        for (int i = 0; i < n; i++) {
            int j = (n - i) & (n - 1);
            cpx fl = (in[0][i] + conj(in[0][j])) * cpx{0.5, 0}, fs = (in[0][i] - conj(in[0][j])) * cpx{0, -0.5},
                gl = (in[1][i] + conj(in[1][j])) * cpx{0.5, 0}, gs = (in[1][i] - conj(in[1][j])) * cpx{0, -0.5};
            out[0][-i & (n - i)] = (fl * gl) + (fl * gs) * cpx{0, 1};
            out[1][-i & (n - i)] = (fs * gl) + (fs * gs) * cpx{0, 1};
        }
        fft(out[0], n), fft(out[1], n);
        for (int i = 0; i < n; i++) {
            out[0][i] /= n, out[1][i] /= n;
            ll av = round(out[0][i].real());
            ll bv = round(out[0][i].imag()) + round(out[1][i].real());
            ll cv = round(out[1][i].imag());
            av %= MOD, bv %= MOD, cv %= MOD;
            res[i] = av * cut * cut + bv * cut + cv;
            res[i] = (res[i] % MOD + MOD) % MOD;
        }
        return res;
    }
};
} // namespace FFTMod
namespace brute {
vector<ll> multiply(vector<int> a, vector<int> b) {
    vector<ll> res(a.size() + b.size() - 1);
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            ll add = (ll)a[i] * b[j] % MOD;
            res[i + j] += (res[i + j] + add >= MOD ? add - MOD : add);
        }
    }
    return res;
}

} // namespace brute
struct timeit {
    decltype(chrono::high_resolution_clock::now()) begin;
    const string label;
    timeit(string label = "???") : label(label) { begin = chrono::high_resolution_clock::now(); }
    ~timeit() {
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - begin).count();
        cerr << duration << "ms elapsed [" << label << "]" << endl;
    }
};
const int MAXN = 1 << 6;
mine::NTT<MAXN * 2> myntt;
FFTMod::FFTMod<MAXN * 2, MOD> myfftmod;
int lg2(int n) { return 32 - __builtin_clz(n); }
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<int> a;
    vector<int> b;
    for (int i = 0; i < MAXN; i++) {
        a.push_back(rand() % MOD);
        b.push_back(rand() % MOD);
    }
    vector<ll> al(MAXN), bl(MAXN);
    for (int i = 0; i < MAXN; i++)
        al[i] = a[i], bl[i] = b[i];
    // {
    //     timeit x("mine");
    //     auto res = myntt.multiply(al, bl);
    //     cout << (res[20] + MOD) % MOD << endl;
    // }
    // {
    //     timeit x("regular operations kactl");
    //     auto res = regkactl::conv(al, bl);
    //     cout << (res[20] + MOD) % MOD << endl;
    // }
    int iters = 1000;
    {
        timeit x("new kactl");
        unsigned ans = 0;
        for (int i = 0; i < iters; i++) {
            // auto res = myntt.multiply(al, bl);
            auto res = newkactl::conv(al, bl);
            ans += (res[0] + MOD) % MOD;
        }
        cout << ans << endl;
    }
    {
        timeit x("brute force");
        unsigned ans = 0;
        for (int i = 0; i < iters; i++) {
            auto res = brute::multiply(a, b);
            ans += (res[0] + MOD) % MOD;
        }
        cout << ans << endl;
    }

    // {
    //     timeit x("FFT Mod");
    //     auto res = myfftmod.multiply(a, b);
    //     cout << (res[20] + MOD) % MOD << endl;
    // }
    // {
    //     timeit x("old kactl");
    //     auto res = oldkactl::conv(al, bl);
    //     cout << (res[20] + MOD) % MOD << endl;
    // }
}