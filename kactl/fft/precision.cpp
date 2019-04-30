#include <bits/stdc++.h>

using namespace std;
#define all(x) begin(x), end(x)
typedef long long ll;
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

typedef complex<double> C;
typedef vector<double> vd;

void fft(vector<C> &a, int n, int L) {
    vector<C> rt(n, 1);
    vi rev(n);
    rep(i, 0, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    for (int k = 2; k < n; k *= 2) {
        C z[] = {1, polar(1.0, M_PI / k)};
        rep(i, k, 2 * k) rt[i] = rt[i / 2] * z[i & 1];
    }
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
    vector<C> in(n), out(n);
    copy(all(a), begin(in));
    rep(i, 0, sz(b)) in[i].imag(b[i]);
    fft(in, n, L);
    trav(x, in) x *= x;
    rep(i, 0, n) out[i] = in[-i & (n - 1)] - conj(in[i]);
    fft(out, n, L);
    rep(i, 0, sz(res)) res[i] = imag(out[i]) / (4 * n);
    return res;
}
template <int M> vi convMod(const vi &a, const vi &b) {
    if (a.empty() || b.empty())
        return {};
    vi res(sz(a) + sz(b) - 1);
    int L = 32 - __builtin_clz(sz(res)), n = 1 << L, cut = sqrt(M);
    vector<C> inl(n), inr(n), outs(n), outl(n);
    rep(i, 0, a.size()) inl[i] = {a[i] / cut, a[i] % cut};
    rep(i, 0, b.size()) inr[i] = {b[i] / cut, b[i] % cut};
    fft(inl, n, L), fft(inr, n, L);
    rep(i, 0, n) {
        int j = -i & (n - 1);
        outl[j] = (inl[i] + conj(inl[j])) * inr[i] / (2.0 * n);
        outs[j] = (inl[i] - conj(inl[j])) * inr[i] / (2.0 * n) / 1i;
    }
    fft(outl, n, L), fft(outs, n, L);
    rep(i, 0, sz(res)) {
        ll av = round(outl[i].real()), cv = round(outs[i].imag());
        ll bv = round(outl[i].imag()) + round(outs[i].real());
        res[i] = int(((av % M * cut + bv % M) * cut + cv % M) % M);
    }
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
}