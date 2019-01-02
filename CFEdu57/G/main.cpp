#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 1e5 + 5;
ll N, K;
ll dp[MAXN * 10][10];
const ll MOD = (119 << 23) + 1, root = 3; // = 998244353
struct NTT {
    // For p < 2ˆ30 there is also e.g. (5 << 25, 3) , (7 << 26, 3),
    // (479 << 21, 3) and (483 << 21, 5). The last two are > 10ˆ9.
    const ll MOD = (119 << 23) + 1, root = 3; // = 998244353
    ll binExp(ll base, ll exp) {
        if (exp == 0)
            return 1;
        return binExp(base * base % MOD, exp / 2) * (exp % 2 == 1 ? base : 1) % MOD;
    }
    void ntt(ll *x, ll *temp, ll *roots, ll N, ll skip) {
        if (N == 1)
            return;
        ll n2 = N / 2;
        ntt(x, temp, roots, n2, skip * 2);
        ntt(x + skip, temp, roots, n2, skip * 2);
        for (ll i = 0; i < N; i++)
            temp[i] = x[i * skip];
        for (ll i = 0; i < n2; i++) {
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
        for (ll i = 1; i < x.size(); i++)
            roots[i] = roots[i - 1] * e % MOD;
        ntt(&x[0], &temp[0], &roots[0], x.size(), 1);
    }
    vector<ll> conv(vector<ll> a, vector<ll> b) {
        ll s = a.size() + b.size() - 1;
        if (s <= 0)
            return {};
        ll L = s > 1 ? 32 - __builtin_clz(s - 1) : 0, n = 1 << L;
        if (s <= 200) {
            vector<ll> c(s);
            for (ll i = 0; i < a.size(); i++)
                for (ll j = 0; j < b.size(); j++)
                    c[i + j] = (c[i + j] + a[i] * b[j]) % MOD;
            return c;
        }
        a.resize(n);
        ntt(a);
        b.resize(n);
        ntt(b);
        ll d = binExp(n, MOD - 2);
        for (ll i = 0; i < n; i++)
            a[i] = a[i] * b[i] % MOD * d % MOD;
        ntt(a, true);
        a.resize(s);
        for (auto &i : a)
            i = i < 0 ? i + MOD : i;
        return a;
    }
};
NTT ntt;
vector<ll> fftExp(vector<ll> a, ll pow) {
    vector<ll> ans(1, 1);
    while (pow > 0) {
        if (pow & 1)
            ans = ntt.conv(ans, a);
        a = ntt.conv(a, a);
        cout << a.size() << endl;
        pow >>= 1;
    }
    return ans;
}
vector<ll> digits(10);
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;
    for (ll i = 0; i < K; i++) {
        ll t;
        cin >> t;
        digits[t] = 1;
    }
    auto res = fftExp(digits, N / 2);
    ll ans = 0;
    for (auto i : res) {
        ans += (i * i) % MOD;
        ans %= MOD;
    }
    cout << ans << endl;
}