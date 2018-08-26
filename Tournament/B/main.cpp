#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 1e6 + 5;
bool sieve[MAXN];
bool isPrime[MAXN];
vector<int> primeFactors[MAXN];
vector<ll> primes;
ll N, X, K;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (ll i = 2; i < MAXN; i++) {
        if (sieve[i])
            continue;
        for (ll j = i; j < MAXN; j += i) {
            primeFactors[j].push_back(i);
            sieve[j] = true;
        }
    }
    cin >> N;
    ll ans = 0;
    for (ll i = 0; i < N; i++) {
        cin >> X >> K;
        ans += primeFactors[X][K - 1];
    }
    cout << ans << endl;
}