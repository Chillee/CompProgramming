#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 1e5 + 5;
const ll MOD = 1e9 + 7;
ll mobius[MAXN];
bool sieve[MAXN];
ll fac[MAXN], invFac[MAXN];
vector<ll> primes;
ll bin_exp(ll base, ll exp) {
    if (exp == 0)
        return 1;
    return bin_exp(base * base % MOD, exp / 2) * (exp % 2 == 1 ? base : 1) % MOD;
}

ll mod_inv(ll a) { return bin_exp(a, MOD - 2); }
void calc() {
    fac[0] = 1;
    invFac[0] = 1;
    for (ll i = 1; i < MAXN; i++) {
        fac[i] = (fac[i - 1] * i) % MOD;
        invFac[i] = mod_inv(fac[i]);
    }
    mobius[1] = 1;
    for (ll i = 2; i < MAXN; i++) {
        if (!sieve[i]) {
            primes.push_back(i);
            mobius[i] = -1;
        }
        for (ll j = 0; j < primes.size() && i * primes[j] < MAXN; j++) {
            sieve[i * primes[j]] = true;
            if (i % primes[j] == 0) {
                mobius[i * primes[j]] = 0;
                break;
            }
            mobius[i * primes[j]] = mobius[i] * -1;
        }
    }
}

ll nCr(ll n, ll r) {
    if (n < r)
        return 0;
    ll num = fac[n];
    ll denom = invFac[r] * invFac[n - r];
    denom %= MOD;
    return (num * denom) % MOD;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    calc();
    ll Q;
    cin >> Q;
    for (ll i = 0; i < Q; i++) {
        ll N, F;
        cin >> N >> F;
        ll ans = 0;
        for (ll j = 1; j * j <= N; j++) {
            if (N % j != 0)
                continue;
            ans += mobius[j] * nCr(N / j - 1, F - 1);
            ans += MOD;
            ans %= MOD;
            if (j * j != N) {
                ans += mobius[N / j] * nCr(j - 1, F - 1);
                ans += MOD;
                ans %= MOD;
            }
        }
        cout << ans << endl;
    }
}