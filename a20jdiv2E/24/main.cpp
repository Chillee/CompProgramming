#include <bits/stdc++.h>

using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

typedef long long ll;
unsigned hash_f(unsigned x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}
struct chash {
    ll operator()(ll x) const { return hash_f(x); }
};
const ll MAXN = 1e5 + 5;
const ll MOD = 1e9 + 7;
ll N, K, A[MAXN];
gp_hash_table<ll, ll> mapping;
ll cnt[1050];

bool isLucky(ll x) {
    while (x > 0) {
        if (x % 10 != 7 && x % 10 != 4)
            return false;
        x /= 10;
    }
    return true;
}
ll bin_exp(ll base, ll exp) {
    if (exp == 0)
        return 1;
    return bin_exp(base * base % MOD, exp / 2) * (exp % 2 == 1 ? base : 1) % MOD;
}

ll mod_inv(ll a) { return bin_exp(a, MOD - 2); }
ll fac[MAXN];
ll ncr(ll n, ll k) {
    if (n < k)
        return 0;
    ll num = fac[n];
    ll denom = (fac[k] * fac[n - k]) % MOD;
    return (num * mod_inv(denom)) % MOD;
}

ll dp[1050][1050];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    fac[0] = 1;
    for (ll i = 1; i < MAXN; i++) {
        fac[i] = (fac[i - 1] * i) % MOD;
    }
    cin >> N >> K;
    for (ll i = 0; i < N; i++) {
        cin >> A[i];
    }
    ll unlucky = N;
    for (ll i = 0; i < N; i++) {
        if (isLucky(A[i]) && mapping.find(A[i]) == mapping.end()) {
            mapping.insert({A[i], mapping.size()});
        }
    }
    for (ll i = 0; i < N; i++) {
        if (mapping.find(A[i]) != mapping.end()) {
            cnt[mapping[A[i]]]++;
            unlucky--;
        }
    }
    dp[0][0] = 1;
    for (ll i = 0; i < mapping.size(); i++) {
        for (ll j = 0; j <= i; j++) {
            dp[i + 1][j] += dp[i][j];
            dp[i + 1][j] %= MOD;
            dp[i + 1][j + 1] += dp[i][j] * cnt[i];
            dp[i + 1][j + 1] %= MOD;
        }
    }
    ll ans = 0;
    for (ll j = 0; j <= mapping.size(); j++) {
        ans += dp[mapping.size()][j] * ncr(unlucky, K - j);
        ans %= MOD;
    }
    cout << ans << endl;
}