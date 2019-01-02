#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MOD = 998244353;
const int MAXN = 1e6 + 5;
int N;
ll bin_exp(ll base, ll exp) {
    if (exp == 0)
        return 1;
    return bin_exp(base * base % MOD, exp / 2) * (exp % 2 == 1 ? base : 1) % MOD;
}

ll mod_inv(ll a) { return bin_exp(a, MOD - 2); }
ll fac[MAXN], invfac[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    fac[0] = 1;
    invfac[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fac[i] = (fac[i - 1] * i) % MOD;
        invfac[i] = mod_inv(fac[i]);
    }
    cin >> N;
    ll val = 0;

    for (int i = 1; i < N; i++) {
        val += invfac[i];
        val %= MOD;
    }
    val *= fac[N];
    val %= MOD;
    ll res = fac[N] * N;
    res %= MOD;
    cout << (res - val + MOD) % MOD << endl;
}