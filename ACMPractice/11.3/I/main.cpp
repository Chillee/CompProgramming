#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 1e5 + 5;
const ll MOD = 1e9 + 7;
ll T;
ll N, M;
ll bin_exp(ll base, ll exp) {
    if (exp == 0)
        return 1;
    return bin_exp(base * base % MOD, exp / 2) * (exp % 2 == 1 ? base : 1) % MOD;
}

ll mod_inv(ll a) { return bin_exp(a, MOD - 2); }
ll fac[MAXN], facinv[MAXN];
ll ncr(ll n, ll r) {
    ll num = fac[n];
    ll denom = (facinv[r] * facinv[n - r]) % MOD;
    return (num * denom) % MOD;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    fac[0] = 1;
    for (ll i = 1; i < MAXN; i++) {
        fac[i] = (fac[i - 1] * i) % MOD;
    }
    for (ll i = 0; i < MAXN; i++) {
        facinv[i] = mod_inv(fac[i]);
    }
    cin >> T;
    for (ll t = 0; t < T; t++) {
        cin >> N >> M;
        cout << ncr(N, M - 1) << ' ' << ncr(N - 1, M - 1) << endl;
    }
}