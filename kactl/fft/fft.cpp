// #pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef complex<double> C;
typedef vector<double> vd;

void fft(vector<C> &a, vector<C> &rt, vi &rev, int n) {
    rep(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k) {
#pragma ivdep
            rep(j, 0, k) {
                // C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
                auto x = (double *)&rt[j + k], y = (double *)&a[i + j + k]; /// exclude-line
                C z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);  /// exclude-line
                a[i + j + k] = a[i + j] - z;
                a[i + j] += z;
            }
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

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
}