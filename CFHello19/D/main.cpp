#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MOD = 1e9 + 7;
const ll MAXI = 1e3 + 5;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

struct chash {
    const ll RANDOM = (long long)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
    static unsigned long long hash_f(unsigned long long x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    static unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }
    ll operator()(ll x) const { return hash_f(x) ^ RANDOM; }
};

struct frac {
    ll n, d;
    frac() { n = 0, d = 0; }
    frac(ll _n, ll _d) { n = _n, d = _d; }
};

frac operator+(const frac &l, const frac &r) { return frac((l.n * r.d % MOD + r.n * l.d % MOD) % MOD, l.d * r.d % MOD); }
frac operator*(const frac &l, const frac &r) { return frac(l.n * r.n % MOD, l.d * r.d % MOD); }
frac operator*(const frac &l, ll r) { return l * frac(r, 1); }
frac operator*(ll r, const frac &l) { return l * r; }

ll N, K;
ll invs[MAXI];
const ll MAXUNIQUE = 100;
bool vis[MAXUNIQUE];
frac lp[MAXUNIQUE][MAXUNIQUE];
gp_hash_table<ll, ll, chash> fact;

ll bin_exp(ll base, ll exp) {
    if (exp == 0)
        return 1;
    return bin_exp(base * base % MOD, exp / 2) * (exp % 2 == 1 ? base : 1) % MOD;
}

ll mod_inv(ll a) { return bin_exp(a, MOD - 2); }

const ll MAXN = 5e7 + 5;
bool sieve[MAXN];
vector<ll> primes;
void calc() {
    for (ll i = 2; i < MAXN; i++) {
        if (!sieve[i])
            primes.push_back(i);
        for (ll j = 0; j < primes.size() && i * primes[j] < MAXN; j++) {
            sieve[primes[j] * i] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}
frac cur[MAXUNIQUE], old[MAXUNIQUE];
signed main() {
    for (ll i = 1; i < MAXI; i++)
        invs[i] = mod_inv(i);

    calc();
    cin >> N >> K;
    for (auto i : primes) {
        ll cnt = 0;
        while (N % i == 0) {
            N /= i;
            cnt++;
        }
        if (cnt > 0) {
            fact[i] = cnt;
            vis[cnt] = true;
        }
        if (N == 1)
            break;
    }
    if (N != 1) {
        fact[N] = 1;
        vis[1] = true;
    }
    for (ll len = 1; len < MAXUNIQUE; len++) {
        if (!vis[len])
            continue;

        fill(cur, cur + len + 1, frac(0, 1));
        cur[len] = frac(1, 1);

        for (ll i = 0; i < K; i++) {
            fill(old, old + len + 1, frac(0, 1));
            for (ll j = 0; j <= len; j++)
                for (ll k = 0; k <= j; k++)
                    old[k] = old[k] + cur[j] * invs[j + 1];

            copy(old, old + MAXUNIQUE, cur);
        }

        for (ll i = 0; i <= len; i++) {
            lp[len][i] = cur[i];
        }
    }
    frac res = frac(1, 1);
    for (auto fc : fact) {
        frac sum = frac(0, 1);
        ll prod = 1;
        for (ll i = 0; i <= fc.second; i++) {
            sum = sum + prod * lp[fc.second][i];
            prod = prod * fc.first % MOD;
        }
        res = res * sum;
    }
    assert(res.n >= 0 && res.n < MOD);
    assert(res.d >= 0 && res.d < MOD);
    cout << res.n * mod_inv(res.d) % MOD << endl;
}