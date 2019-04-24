#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll MAXN = 505;
const ll MOD = 1e9 + 7;
string S;
ll dp[MAXN][MAXN];
ll bin_exp(ll base, ll exp) {
    if (exp == 0)
        return 1;
    return bin_exp(base * base % MOD, exp / 2) * (exp % 2 == 1 ? base : 1) % MOD;
}

ll mod_inv(ll a) { return bin_exp(a, MOD - 2); }
ll fac[MAXN], ifac[MAXN];
ll nCr(ll n, ll r) {
    ll res = fac[n] * ifac[r] % MOD;
    return res * ifac[n - r] % MOD;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    fac[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fac[i] = (fac[i - 1] * i) % MOD;
        ifac[i] = mod_inv(fac[i]);
    }
    cin >> S;
    for (ll i = 0; i < S.size() - 1; i++) {
        if (S[i] == S[i + 1])
            dp[i][i + 1] = 1;
    }
    for (ll l = 3; l < S.size(); l += 2) {
        for (ll i = 0; i < S.size() - l; i++) {
            for (ll k = i; k < i + l; k++) {
                if (S[i + l] != S[k])
                    continue;
                ll mul = 1;
                ll a = -1, b = -1;
                if (k > i) {
                    a = dp[i][k - 1];
                }
                if (k + 1 < i + l) {
                    b = dp[k + 1][i + l - 1];
                }
                if (a != -1 && b == -1) {
                    int cnt = max(a, b);
                    dp[i][i + l] += ((l + 1) / 2 * cnt) % MOD;
                    dp[i][i + l] %= MOD;
                } else if (a == -1 && b != -1) {
                    dp[i][i + l] += b;
                    dp[i][i + l] %= MOD;
                } else if (a != -1 && b != -1) {
                    int numActions = (k - i + i + l - k + 1) / 2;
                    int chf = nCr(numActions, (k - i) / 2);
                    dp[i][i + l] += (chf * a) % MOD * b % MOD;
                }
                dp[i][i + l] %= MOD;
            }
        }
    }
    // for (ll i = 0; i < S.size(); i++) {
    //     for (ll j = 0; j < S.size(); j++) {
    //         cout << dp[i][j] << ' ';
    //     }
    //     cout << endl;
    // }
    // c
    ll ans = dp[0][S.size() - 1];
    cout << ans << endl;
    // for (ll i = 0; i < S.size(); i++) {
    //     // cout << dp[0][i] << ' ' << dp[i + 1][S.size() - 1] << endl;
    //     ans += dp[0][i] * dp[i + 1][S.size() - 1];
    //     ans %= MOD;
    // }
}