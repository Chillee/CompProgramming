#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll N;
const ll MAXN = 505;
const ll MOD = 1e9 + 7;
ll dp[MAXN * MAXN];
ll bin_exp(ll base, ll pow) {
    if (pow == 0)
        return 1;
    return bin_exp(base * base % MOD, pow / 2) * (pow % 2 == 0 ? 1 : base) % MOD;
}

ll mod_inv(ll a) { return bin_exp(a, MOD - 2); }
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    ll cnt = N * (N + 1) / 2;
    if (cnt % 2 == 1) {
        cout << 0 << endl;
        return 0;
    }
    cnt /= 2;
    dp[0] = 1;
    for (ll i = 1; i <= N; i++) {
        for (ll j = cnt - i; j >= 0; j--) {
            dp[j + i] += dp[j];
            dp[j + i] %= MOD;
        }
    }
    cout << (dp[cnt] * mod_inv(2)) % MOD << endl;
}