#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 1005;
const ll MOD = 1e9 + 7;
ll N, M, K;
ll bin_exp(ll base, ll exp) {
    if (exp == 0)
        return 1;
    return bin_exp(base * base % MOD, exp / 2) * (exp % 2 == 1 ? base : 1) % MOD;
}

ll mod_inv(ll a) { return bin_exp(a, MOD - 2); }
ll combo(ll n, ll k) {
    if (k > n) {
        return 0;
    }
    ll num = 1;
    for (ll i = 1; i <= n; i++) {
        num = (num * i) % MOD;
    }
    ll denom = 1;
    for (ll i = 1; i <= k; i++) {
        denom = (denom * i) % MOD;
    }
    for (ll i = 1; i <= n - k; i++) {
        denom = (denom * i) % MOD;
    }
    return (num * mod_inv(denom)) % MOD;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M >> K;
    cout << (combo(N - 1, 2 * K) * combo(M - 1, 2 * K)) % MOD << endl;
}