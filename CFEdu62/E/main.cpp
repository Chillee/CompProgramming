#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MOD = 998244353;
const ll MAXN = 2e5 + 5;
ll N, K;
vector<ll> odd, even;
ll g[MAXN], f[MAXN];
ll bin_exp(ll base, ll exp) {
    if (exp == 0)
        return 1;
    return bin_exp(base * base % MOD, exp / 2) * (exp % 2 == 1 ? base : 1) % MOD;
}

ll mod_inv(ll a) { return bin_exp(a, MOD - 2); }
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;
    g[0] = (K - 1);
    g[1] = (K - 1) * (K - 2) % MOD;
    for (ll i = 2; i < MAXN; i++) {
        g[i] = ((K - 2) * g[i - 1] % MOD + (K - 1) * g[i - 2] % MOD) % MOD;
    }
    f[0] = 0;
    for (ll i = 1; i < MAXN; i++) {
        f[i] = g[i - 1];
    }
    for (ll i = 0; i < N; i++) {
        ll x;
        cin >> x;
        if (i & 1)
            odd.push_back(x);
        else
            even.push_back(x);
    }
    ll ans = 1;
    for (ll t = 0; t < 2; t++) {
        for (ll i = 0; i < odd.size(); i++) {
            if (odd[i] != -1) {
                if (i != 0 && odd[i] == odd[i - 1]) {
                    cout << 0 << endl;
                    return 0;
                }
                continue;
            }
            ll beg = (i > 0 ? odd[i - 1] : -1);
            ll len = 1;
            while (odd[i + 1] == -1)
                i++, len++;
            ll end = (i < odd.size() - 1 ? odd[i + 1] : -1);
            ll mult = 0;
            if (beg == -1 && end == -1) {
                if (len == 1) {
                    mult = K;
                } else {
                    mult = K * ((g[len - 2] + f[len - 2]) % MOD) % MOD;
                }
            } else if ((beg == -1 && end != -1) || (beg != -1 && end == -1)) {
                mult = g[len - 1] + f[len - 1];
            } else if (beg == end) {
                mult = f[len];
            } else {
                mult = (g[len] * mod_inv(K - 1)) % MOD;
            }
            ans *= mult;
            ans %= MOD;
        }
        swap(odd, even);
    }
    cout << ans << endl;
}