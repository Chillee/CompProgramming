#pragma GCC optimize("O3")
#include <bits/stdc++.h>

#define all(x) x.begin(), x.end()
using namespace std;

typedef long long ll;
const ll MOD = 1e9 + 7;
const ll MAXN = 1e6 + 5;
const ll MAXM = 1005;
ll fac[2 * MAXN], ifac[2 * MAXN];
ll nCr(ll n, ll r) {
    ll num = fac[n];
    ll denom = ifac[r] * ifac[n - r] % MOD;
    return num * denom % MOD;
}
ll numPaths(ll x, ll y) {
    if (x == 0 || y == 0)
        return 1;
    return nCr(x + y, x);
}
ll dp[MAXM];
ll N, M;
vector<array<ll, 2>> traps;
ll bin_exp(ll base, ll exp) {
    if (exp == 0)
        return 1;
    return bin_exp(base * base % MOD, exp / 2) * (exp % 2 == 1 ? base : 1) % MOD;
}

ll mod_inv(ll a) { return bin_exp(a, MOD - 2); }
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    fac[0] = 1;
    for (ll i = 1; i < 2 * MAXN; i++) {
        fac[i] = fac[i - 1] * i % MOD;
        ifac[i] = mod_inv(fac[i]);
    }
    cin >> N >> M;
    traps.resize(M + 1);
    for (ll i = 0; i < M; i++)
        cin >> traps[i][0] >> traps[i][1];
    traps[M] = {N, N};
    for (auto &i : traps)
        i[0]--, i[1]--;

    for (ll i = 0; i < M; i++) {
        for (ll j = 0; j < M; j++) {
            if (i == j)
                continue;
        }
    }
    sort(all(traps));
    for (ll i = 0; i <= M; i++) {
        dp[i] = numPaths(traps[i][0], traps[i][1]);
        for (ll j = 0; j < i; j++) {
            if (traps[j][0] > traps[i][0] || traps[j][1] > traps[i][1])
                continue;
            dp[i] -= dp[j] * numPaths(traps[i][0] - traps[j][0], traps[i][1] - traps[j][1]) % MOD;
            dp[i] %= MOD;
        }
    }
    cout << (dp[M] + MOD) % MOD << endl;
}