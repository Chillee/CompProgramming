#include <bits/stdc++.h>

#define all(x) begin(x), end(x)

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define sz(x) (int)(x).size()
typedef long long ll;
using namespace std;

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
const int MOD = (119 << 23) + 1;
// const int MOD = 1e9 + 7;
const int MAXN = 1 << 19;
// const int MOD = 1e5 + 7;
namespace mine {
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
        for (int i = 0; i < sz; i++) {
            out[0][i] /= n, out[1][i] /= n;
            ll av = round(out[0][i].real());
            ll bv = round(out[0][i].imag()) + round(out[1][i].real());
            ll cv = round(out[1][i].imag());
            av %= MOD, bv %= MOD, cv %= MOD;
            res[i] = (av * cut * cut + bv * cut + cv) % MOD;
        }
        return res;
    }
};
} // namespace mine
namespace kactlorig {
typedef complex<double> C;
typedef vector<double> vd;
typedef vector<int> vi;

void fft(vector<C> &a, vector<C> &rt, vi &rev, int n) {
    rep(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k)
            rep(j, 0, k) {
                // C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
                auto x = (double *)&rt[j + k], y = (double *)&a[i + j + k]; /// exclude-line
                C z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);  /// exclude-line
                a[i + j + k] = a[i + j] - z;
                a[i + j] += z;
            }
}

vd conv(const vd &a, const vd &b) {
    if (a.empty() || b.empty())
        return {};
    vd res(sz(a) + sz(b) - 1);
    int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
    vector<C> in(n), out(n), rt(n, 1);
    vi rev(n);
    rep(i, 0, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    for (int k = 2; k < n; k *= 2) {
        C z[] = {1, polar(1.0, M_PI / k)};
        rep(i, k, 2 * k) rt[i] = rt[i / 2] * z[i & 1];
    }
    copy(all(a), begin(in));
    rep(i, 0, sz(b)) in[i].imag(b[i]);
    fft(in, rt, rev, n);
    trav(x, in) x *= x;
    rep(i, 0, n) out[i] = in[(n - i) & (n - 1)] - conj(in[i]);
    fft(out, rt, rev, n);
    rep(i, 0, sz(res)) res[i] = imag(out[i]) / (4 * n);
    return res;
}

template <int MOD> vector<ll> convMod(const vi &a, const vi &b) {
    if (a.empty() || b.empty())
        return {};
    vector<ll> res(sz(a) + sz(b) - 1);
    int L = 32 - __builtin_clz(sz(res)), n = 1 << L, cut = sqrt(MOD);
    vector<C> inl(n), inr(n), outs(n), outl(n), rt(n, 1);
    vi rev(n);
    rep(i, 0, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    for (int k = 2; k < n; k *= 2) {
        C z[] = {1, polar(1.0, M_PI / k)};
        rep(i, k, 2 * k) rt[i] = rt[i / 2] * z[i & 1];
    }
    rep(i, 0, a.size()) inl[i] = {a[i] / cut, a[i] % cut};
    rep(i, 0, b.size()) inr[i] = {b[i] / cut, b[i] % cut};
    fft(inl, rt, rev, n), fft(inr, rt, rev, n);
    rep(i, 0, n) {
        int j = (n - i) & (n - 1);
        C fl = (inl[i] + conj(inl[j])) * C{0.5, 0}, fs = (inl[i] - conj(inl[j])) * C{0, -0.5},
          gl = (inr[i] + conj(inr[j])) * C{0.5, 0}, gs = (inr[i] - conj(inr[j])) * C{0, -0.5};
        outl[j] = fl * (gl + gs * C{0, 1});
        outs[j] = fs * (gl + gs * C{0, 1});
    }
    fft(outl, rt, rev, n), fft(outs, rt, rev, n);
    rep(i, 0, sz(res)) {
        outl[i] /= n, outs[i] /= n;
        ll av = round(outl[i].real());
        ll bv = round(outl[i].imag()) + round(outs[i].real());
        ll cv = round(outs[i].imag());
        av %= MOD, bv %= MOD, cv %= MOD;
        res[i] = (av * cut * cut + bv * cut + cv) % MOD;
    }
    return res;
}

} // namespace kactlorig
namespace NTT {
template <int maxn> struct NTT {
    constexpr static int lg2(int n) { return 32 - __builtin_clz(n - 1); }
    const static int MAXN = 1 << lg2(maxn), MOD = (119 << 23) + 1, root = 3;
    int rev[MAXN], rt[MAXN];

    int mul(int a, int b) { return (long long)a * b % MOD; }
    int sub(int a, int b) { return b > a ? a - b + MOD : a - b; }
    int add(int a, int b) { return a + b >= MOD ? a + b - MOD : a + b; }

    int binExp(int base, long long exp) {
        if (exp == 0)
            return 1;
        return mul(binExp(mul(base, base), exp / 2), exp & 1 ? base : 1);
    }
    NTT() {
        rt[1] = 1;
        for (int k = 1; k < lg2(MAXN); k++) {
            int z[] = {1, binExp(root, (MOD - 1) >> (k + 1))};
            for (int i = (1 << k); i < 2 << k; i++)
                rt[i] = mul(rt[i / 2], z[i & 1]);
        }
    }
    void ntt(int *a, int n) {
        for (int i = 0; i < n; i++)
            rev[i] = (rev[i / 2] | (i & 1) << lg2(n)) / 2;
        for (int i = 0; i < n; i++)
            if (i < rev[i])
                swap(a[i], a[rev[i]]);
        for (int k = 1; k < n; k *= 2)
            for (int i = 0; i < n; i += 2 * k)
                for (int j = 0; j < k; j++) {
                    int z = mul(rt[j + k], a[i + j + k]);
                    a[i + j + k] = sub(a[i + j], z);
                    a[i + j] = add(a[i + j], z);
                }
    }
    int in[2][MAXN];
    vector<int> multiply(const vector<int> &a, const vector<int> &b) {
        fill(all(in[0]), 0), fill(all(in[1]), 0);
        if (a.empty() || b.empty())
            return {};
        int sz = a.size() + b.size() - 1, n = 1 << lg2(sz);
        copy(all(a), in[0]), copy(all(b), in[1]);
        ntt(in[0], n), ntt(in[1], n);
        int invN = binExp(n, MOD - 2);
        for (int i = 0; i < n; i++)
            in[0][i] = mul(mul(in[0][i], in[1][i]), invN);
        reverse(in[0] + 1, in[0] + n);
        ntt(in[0], n);
        return vector<int>(in[0], in[0] + sz);
    }
};
} // namespace NTT

namespace NTTCRT {
template <int maxn, int MOD = 998244353, int root = 62> struct NTT {
    constexpr static int lg2(int n) { return 32 - __builtin_clz(n - 1); }
    const static int MAXN = 1 << lg2(maxn);
    int rev[MAXN], rt[MAXN];

    int mul(int a, int b) { return (long long)a * b % MOD; }
    int sub(int a, int b) { return b > a ? a - b + MOD : a - b; }
    int add(int a, int b) { return a + b >= MOD ? a + b - MOD : a + b; }

    int binExp(int base, long long exp) {
        if (exp == 0)
            return 1;
        return mul(binExp(mul(base, base), exp / 2), exp & 1 ? base : 1);
    }
    NTT() {
        rt[1] = 1;
        for (int k = 1; k < lg2(MAXN); k++) {
            int z[] = {1, binExp(root, (MOD - 1) >> (k + 1))};
            for (int i = (1 << k); i < 2 << k; i++)
                rt[i] = mul(rt[i / 2], z[i & 1]);
        }
    }
    void ntt(int *a, int n) {
        for (int i = 0; i < n; i++)
            rev[i] = (rev[i / 2] | (i & 1) << lg2(n)) / 2;
        for (int i = 0; i < n; i++)
            if (i < rev[i])
                swap(a[i], a[rev[i]]);
        for (int k = 1; k < n; k *= 2)
            for (int i = 0; i < n; i += 2 * k)
                for (int j = 0; j < k; j++) {
                    int z = mul(rt[j + k], a[i + j + k]);
                    a[i + j + k] = sub(a[i + j], z);
                    a[i + j] = add(a[i + j], z);
                }
    }
    int in[2][MAXN];
    vector<int> multiply(const vector<int> &a, const vector<int> &b) {
        fill(all(in[0]), 0), fill(all(in[1]), 0);
        if (a.empty() || b.empty())
            return {};
        int sz = a.size() + b.size() - 1, n = 1 << lg2(sz);
        copy(all(a), in[0]), copy(all(b), in[1]);
        ntt(in[0], n), ntt(in[1], n);
        int invN = binExp(n, MOD - 2);
        for (int i = 0; i < n; i++)
            in[0][i] = mul(mul(in[0][i], in[1][i]), invN);
        reverse(in[0] + 1, in[0] + n);
        ntt(in[0], n);
        return vector<int>(in[0], in[0] + sz);
    }
};
constexpr int mods[] = {(119 << 23) + 1, (5 << 25) + 1, (7 << 26) + 1};
NTT<2 * MAXN, mods[0]> ntt1;
NTT<2 * MAXN, mods[1]> ntt2;
NTT<2 * MAXN, mods[2]> ntt3;

typedef __int128_t lll;
lll euclid(lll a, lll b, lll &x, lll &y) {
    if (b) {
        lll d = euclid(b, a % b, y, x);
        return y -= a / b * x, d;
    }
    return x = 1, y = 0, a;
}
lll chinese(lll a, lll m, lll b, lll n) { // x = a %m, x = b%n, gcd(m,n)=1
    lll x, y;
    euclid(m, n, x, y);
    lll ret = a * (y + m) % m * n + b * (x + n) % n * m;
    if (ret >= m * n)
        ret -= m * n;
    return ret;
}
vector<ll> convMod(vector<int> a, vector<int> b, int mod = 1e9 + 7) {
    vector<int> res1, res2, res3;
    {
        timeit y("ntt");
        res1 = ntt1.multiply(a, b);
        res2 = ntt2.multiply(a, b);
        res3 = ntt3.multiply(a, b);
    }
    vector<ll> res;
    {
        timeit x("crt portion");
        for (int i = 0; i < res1.size(); i++) {
            lll cur = chinese(res1[i], mods[0], res2[i], mods[1]);
            cur = chinese(cur, (lll)mods[0] * mods[1], res3[i], mods[2]);
            res.push_back(cur % mod);
        }
    }
    return res;
}

} // namespace NTTCRT

namespace reuse {
typedef complex<double> C;
typedef vector<double> vd;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
void fft(vector<C> &a, vector<C> &rt, vi &rev, int n) {
    rep(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k)
            rep(j, 0, k) {
                // C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
                auto x = (double *)&rt[j + k], y = (double *)&a[i + j + k]; /// exclude-line
                C z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);  /// exclude-line
                a[i + j + k] = a[i + j] - z;
                a[i + j] += z;
            }
}

vd conv(const vd &a, const vd &b) {
    if (a.empty() || b.empty())
        return {};
    vd res(sz(a) + sz(b) - 1);
    int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
    vector<C> in(n), out(n), rt(n, 1);
    vi rev(n);
    rep(i, 0, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    for (int k = 2; k < n; k *= 2) {
        C z[] = {1, polar(1.0, M_PI / k)};
        rep(i, k, 2 * k) rt[i] = rt[i / 2] * z[i & 1];
    }
    copy(all(a), begin(in));
    rep(i, 0, sz(b)) in[i].imag(b[i]);
    fft(in, rt, rev, n);
    trav(x, in) x *= x;
    rep(i, 0, n) out[i] = in[-i & (n - 1)] - conj(in[i]);
    fft(out, rt, rev, n);
    rep(i, 0, sz(res)) res[i] = imag(out[i]) / (4 * n);
    return res;
}
template <int MOD> vector<ll> convMod(const vi &a, const vi &b) {
    if (a.empty() || b.empty())
        return {};
    ll cut = sqrt(MOD);
    vector<double> ah(sz(a)), al(ah), bh(sz(b)), bl(bh);
    rep(i, 0, sz(a)) ah[i] = a[i] / cut, al[i] = a[i] % cut;
    rep(i, 0, sz(b)) bh[i] = b[i] / cut, bl[i] = b[i] % cut;
    auto h = conv(ah, bh), l = conv(al, bl);
    auto m1 = conv(ah, bl), m2 = conv(al, bh);
    vector<ll> res(h.size());
    for (int i = 0; i < res.size(); i++) {
        ll av = round(h[i]);
        ll bv = round(m1[i]) + round(m2[i]);
        ll cv = round(l[i]);
        av %= MOD, bv %= MOD, cv %= MOD;
        res[i] = (av * cut * cut + bv * cut + cv) % MOD;
    }
    return res;
}
} // namespace reuse

namespace kactl2 {
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<double> vd;
typedef complex<double> C;
typedef complex<double> Cd;
double count;
typedef vector<ll> vl;

void fft(vector<C> &a, int n, int L) {
	vi rev(n); vector<C> rt(n, 1);
	rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    for (int k = 2; k < n; k *= 2) {
        C z[] = {1, polar(1.0, M_PI / k)};
        rep(i, k, 2 * k) rt[i] = C(rt[i / 2]) * z[i & 1];
    }
	rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
			// C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
			auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
			C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
			a[i + j + k] = a[i + j] - z;
			a[i + j] += z;
		}
}
vd conv(const vd &a, const vd &b) {
	if (a.empty() || b.empty()) return {};
	vd res(sz(a) + sz(b) - 1);
	int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
	vector<C> in(n), out(n), rt;
	copy(all(a), begin(in));
	rep(i,0,sz(b)) in[i].imag(b[i]);
	fft(in, n, L);
	trav(x, in) x *= x;
	rep(i,0,n) out[i] = in[-i & (n - 1)] - conj(in[i]);
	fft(out, n, L);
	rep(i,0,sz(res)) res[i] = imag(out[i]) / (4 * n);
	return res;
}

template <int M> vl convMod(const vl &a, const vl &b) {
    if (a.empty() || b.empty())
        return {};
    vl res(sz(a) + sz(b) - 1);
    int B = 32 - __builtin_clz(sz(res)), n = 1 << B, cut = int(sqrt(M));
    vector<C> L(n), R(n), outs(n), outl(n);
    rep(i, 0, sz(a)) L[i] = Cd(a[i] / cut, a[i] % cut);
    rep(i, 0, sz(b)) R[i] = Cd(b[i] / cut, b[i] % cut);
    fft(L, n, B), fft(R, n, B);
    rep(i, 0, n) {
        int j = -i & (n - 1);
        outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
        outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
    }
    fft(outl, n, B), fft(outs, n, B);
    rep(i, 0, sz(res)) {
        ll av = ll(outl[i].real() + .5), cv = ll(outs[i].imag() + .5);
        ll bv = ll(outl[i].imag() + .5) + ll(outs[i].real() + .5);
        res[i] = ((av % M * cut + bv % M) * cut + cv % M) % M;
    }
    return res;
}
}
namespace kactl {
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<double> vd;
typedef complex<double> C;
typedef complex<long double> Cd;
double count;
typedef vector<ll> vl;

void fft(vector<C> &a) {
    int n = sz(a), L = 31 - __builtin_clz(n);
	vi rev(n); static vector<C> rt(2, 1);
	rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    for (static int k = 2; k < n; k *= 2) {
        rt.resize(n);
        Cd z[] = {1, polar(1.0L, M_PIl / k)};
        rep(i, k, 2 * k) rt[i] = Cd(rt[i / 2]) * z[i & 1];
    }
	rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
			// C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
			auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
			C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
			a[i + j + k] = a[i + j] - z;
			a[i + j] += z;
		}
}
vd conv(const vd &a, const vd &b) {
	if (a.empty() || b.empty()) return {};
	vd res(sz(a) + sz(b) - 1);
	int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
	vector<C> in(n), out(n), rt;
	copy(all(a), begin(in));
	rep(i,0,sz(b)) in[i].imag(b[i]);
	fft(in);
	trav(x, in) x *= x;
	rep(i,0,n) out[i] = in[-i & (n - 1)] - conj(in[i]);
	fft(out);
	rep(i,0,sz(res)) res[i] = imag(out[i]) / (4 * n);
	return res;
}
template <int M> vl convMod(const vl &a, const vl &b) {
    if (a.empty() || b.empty())
        return {};
    vl res(sz(a) + sz(b) - 1);
    int B = 32 - __builtin_clz(sz(res)), n = 1 << B, cut = int(sqrt(M));
    vector<C> L(n), R(n), outs(n), outl(n), rt;
    rep(i, 0, sz(a)) L[i] = C(a[i] / cut, a[i] % cut);
    rep(i, 0, sz(b)) R[i] = C(b[i] / cut, b[i] % cut);
    fft(L), fft(R);
    rep(i, 0, n) {
        int j = -i & (n - 1);
        outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
        outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
    }
    fft(outl), fft(outs);
    rep(i, 0, sz(res)) {
        ll av = ll(outl[i].real() + .5), cv = ll(outs[i].imag() + .5);
        ll bv = ll(outl[i].imag() + .5) + ll(outs[i].real() + .5);
        res[i] = ((av % M * cut + bv % M) * cut + cv % M) % M;
    }
    return res;
}
} // namespace kactl

mine::FFTMod<2 * MAXN, MOD> myfft;
NTT::NTT<2 * MAXN> myntt;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    srand(time(0));
    vector<int> a, b;
    for (int i = 0; i < MAXN; i++) {
        a.push_back(rand() % MOD);
        b.push_back(rand() % MOD);
    }
    vector<int> correct(2 * a.size() - 1);
    if (MOD == (119 << 23) + 1) {
        correct = myntt.multiply(a, b);
    } else if (MAXN < 1e4) {
        for (int i = 0; i < a.size(); i++) {
            for (int j = 0; j < b.size(); j++) {
                correct[i + j] = (correct[i + j] + (ll)a[i] * b[j]) % MOD;
            }
        }
    } else {
        auto res = myfft.multiply(a, b);
        for (int i = 0; i < res.size(); i++)
            correct[i] = res[i];
    }
    // {
    //     timeit x("neal");
    //     vector<ll> al, bl;
    //     for (int i = 0; i < MAXN; i++)
    //         al.push_back(a[i]), bl.push_back(b[i]);
    //     auto res = FFTNeal::mod_multiply(a, b, MOD, true);
    //     for (int i = 0; i < res.size(); i++) {
    //         if (res[i] != correct[i])
    //             cout << res[i] << ' ' << correct[i] << endl;
    //         assert(res[i] == correct[i]);
    //     }
    //     cout << endl;
    // }

    {
        vector<ll> al, bl;
        for (int i=0; i<sz(a); i++)
            al.push_back(a[i]), bl.push_back(b[i]);
        timeit x("kactl fft mod");
        vector<ll> res;
        for (int i=0; i<1; i++) {
            res = kactl::convMod<MOD>(al, bl);
        }
        for (int i = 0; i < res.size(); i++) {
            if (res[i] != correct[i])
                cout << res[i] << ' ' << correct[i] << endl;
            assert(res[i] == correct[i]);
        }
    }
    {
        vector<ll> al, bl;
        for (int i=0; i<sz(a); i++)
            al.push_back(a[i]), bl.push_back(b[i]);
        timeit x("kactl double fft mod");
        vector<ll> res;
        for (int i=0; i<1; i++) {
            res = kactl2::convMod<MOD>(al, bl);
        }
        for (int i = 0; i < res.size(); i++) {
            if (res[i] != correct[i])
                cout << res[i] << ' ' << correct[i] << endl;
            assert(res[i] == correct[i]);
        }
    }
    // {
    //     vector<ll> al, bl;
    //     for (int i=0; i<sz(a); i++)
    //         al.push_back(a[i]), bl.push_back(b[i]);
    //     timeit x("kactl fft mod");
    //     int a
    //     // auto res = kactl::convMod<MOD>(al, bl);
    //     // for (int i = 0; i < res.size(); i++) {
    //     //     if (res[i] != correct[i])
    //     //         cout << res[i] << ' ' << correct[i] << endl;
    //     //     assert(res[i] == correct[i]);
    //     // }
    // }
    // vector<double> ad(MAXN), bd(MAXN);
    // for (int i = 0; i < MAXN; i++)
    //     ad[i] = a[i], bd[i] = b[i];
    // {
    //     timeit x("kactl orig");
    //     auto res = kactlorig::conv(ad, bd);
    //     // for (int i = 0; i < res.size(); i++) {
    //     //     if (res[i] != correct[i])
    //     //         cout << res[i] << ' ' << correct[i] << endl;
    //     //     assert(res[i] == correct[i]);
    //     // }
    // }
    // {
    //     timeit x("my ntt");
    //     auto res = myntt.multiply(a, b);
    //     for (int i = 0; i < res.size(); i++) {
    //         assert(res[i] == correct[i]);
    //     }
    // }
    // return 0;
    return 0;
    // {
    //     timeit x("mine");
    //     auto res = myfft.multiply(a, b);
    //     for (int i = 0; i < res.size(); i++) {
    //         if (res[i] != correct[i])
    //             cout << res[i] << ' ' << correct[i] << endl;
    //         assert(res[i] == correct[i]);
    //     }
    // }
    // {
    //     timeit x("ntt crt");
    //     auto res = NTTCRT::convMod(a, b);
    //     for (int i = 0; i < res.size(); i++) {
    //         if (res[i] != correct[i])
    //             cout << res[i] << ' ' << correct[i] << endl;
    //         assert(res[i] == correct[i]);
    //     }
    // }
    // {
    //     timeit x("reuse");
    //     auto res = reuse::convMod<MOD>(a, b);
    //     for (int i = 0; i < res.size(); i++) {
    //         if (res[i] != correct[i])
    //             cout << i << ' ' << res[i] << ' ' << correct[i] << endl;
    //         assert(res[i] == correct[i]);
    //     }
    // }

    // {
    //     timeit x("kactl fft");
    //     vector<double> ad(MAXN), bd(MAXN);
    //     for (int i = 0; i < MAXN; i++)
    //         ad[i] = a[i], bd[i] = b[i];
    //     auto res = kactl::conv(ad, bd);
    //     for (int i = 0; i < res.size(); i++) {
    //         // res[i] = (ll)round(res[i]) % MOD;
    //         int v = (ll)round(res[i]) % MOD;
    //         if (v != correct[i]) {
    //             cout << v << ' ' << correct[i] << ' ' << res[i] << endl;
    //             assert(v == correct[i]);
    //         }
    //     }
    // }
}