#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 1e7 + 5;
const ll MOD = 1e9 + 7;
bool sieve[MAXN];
vector<ll> primes;
ll phi[MAXN];
ll lcm(ll a, ll b) { return a * b / __gcd(a, b); }
ll P, K, N, M;
vector<ll> Ndivs, Mdivs;
ll bin_exp(ll base, ll exp) {
    if (exp == 0)
        return 1;
    return bin_exp(base * base % MOD, exp / 2) * (exp % 2 == 1 ? base : 1) % MOD;
}

ll mod_inv(ll a) { return bin_exp(a, MOD - 2); }

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    phi[1] = 1;
    for (ll i = 2; i < MAXN; i++) {
        if (!sieve[i]) {
            primes.push_back(i);
            phi[i] = i - 1;
        }
        for (ll j = 0; j < primes.size() && i * primes[j] < MAXN; j++) {
            sieve[i * primes[j]] = true;
            if (i % primes[j] == 0) {
                phi[i * primes[j]] = phi[i] * primes[j];
                break;
            }
            phi[i * primes[j]] = phi[i] * phi[primes[j]];
        }
    }
    cin >> P;
    for (ll p = 0; p < P; p++) {
        cin >> K >> N >> M;
        Ndivs.clear(), Mdivs.clear();
        for (ll i = 1; i * i <= N; i++) {
            if (N % i == 0) {
                Ndivs.push_back(i);
                if (i * i != N)
                    Ndivs.push_back(N / i);
            }
        }
        for (ll i = 1; i * i <= M; i++) {
            if (M % i == 0) {
                Mdivs.push_back(i);
                if (i * i != M)
                    Mdivs.push_back(M / i);
            }
        }
        ll ans = 0;
        for (auto i : Ndivs) {
            for (auto j : Mdivs) {
                ll cur = lcm(N / i, M / j);
                cur = bin_exp(2, N * M / cur);
                cur *= phi[N / i];
                cur %= MOD;
                cur *= phi[M / j];
                cur %= MOD;
                ans += cur;
                ans %= MOD;
            }
        }
        cout << K << ' ' << (ans * mod_inv((N * M) % MOD)) % MOD << endl;
    }
}