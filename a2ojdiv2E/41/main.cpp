#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 2e3 + 5;
const ll MOD = 1e9 + 7;
ll bin_exp(ll base, ll exp) {
    if (exp == 0)
        return 1;
    return bin_exp(base * base % MOD, exp / 2) * (exp % 2 == 1 ? base : 1) % MOD;
}

ll mod_inv(ll a) { return bin_exp(a, MOD - 2); }
ll N;
ll fac[MAXN], invfac[MAXN];
ll nCr(ll n, ll r) {
    ll num = fac[n];
    ll denom = invfac[r] * invfac[n - r];
    denom %= MOD;
    return (num * denom) % MOD;
}

set<ll> vals;
ll A[MAXN];
ll cnt, fcnt;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    fac[0] = invfac[0] = 1;
    for (ll i = 1; i < MAXN; i++) {
        fac[i] = (fac[i - 1] * i) % MOD;
        invfac[i] = mod_inv(fac[i]);
    }
    cin >> N;
    for (ll i = 0; i < N; i++) {
        cin >> A[i];
        if (A[i] != -1)
            vals.insert(A[i]);
    }
    for (ll i = 0; i < N; i++) {
        if (A[i] == -1)
            cnt++;
        if (A[i] == -1 && vals.find(i + 1) == vals.end())
            fcnt++;
    }
    ll ans = fac[cnt];
    for (ll i = 1; i <= fcnt; i++) {
        ll cur = (nCr(fcnt, i) * fac[cnt - i]) % MOD;
        if (i % 2 == 1)
            ans -= cur;
        else
            ans += cur;
        ans += MOD;
        ans %= MOD;
    }
    cout << ans << endl;
}