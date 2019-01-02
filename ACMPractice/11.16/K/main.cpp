#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 2505;
const ll MOD = 1e9 + 7;

ll bin_exp(ll base, ll exp) {
    if (exp == 0)
        return 1;
    return bin_exp(base * base % MOD, exp / 2) * (exp % 2 == 1 ? base : 1) % MOD;
}

ll mod_inv(ll a) { return bin_exp(a, MOD - 2); }
ll fac[MAXN];
ll ncr(ll n, ll k) {
    ll num = fac[n];
    ll denom = (fac[k] * fac[n - k]) % MOD;
    return (num * mod_inv(denom)) % MOD;
}
ll N, K;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    fac[0] = 1;
    for (ll i = 1; i < MAXN; i++) {
        fac[i] = (fac[i - 1] * i) % MOD;
    }
    cin >> N >> K;

    for (ll i = 0; i < N - 1; i++) {
        ll t;
        cin >> t;
    }
    ll ans = 0;
    for (ll i = 2; i <= K; i++) {
        ll mul = ((bin_exp(-1, K - i) + MOD) % MOD) * ncr(K, i);
        mul %= MOD;
        mul *= (i * bin_exp(i - 1, N - 1)) % MOD;
        mul %= MOD;
        ans += mul;
        ans %= MOD;
    }
    cout << ans << endl;
}