#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAXN = 1e4 + 5;
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
ll egcd(ll a, ll b, ll &x, ll &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    ll x1, y1;
    ll d = egcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}
ll lcm(ll a, ll b) { return a * b / __gcd(a, b); }
ll N;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    calc();
    cin >> N;
    vector<ll> factors;
    for (ll i = 2; i * i <= N; i++) {
        if (N % i != 0)
            continue;
        if (i * i == N) {
            factors.push_back(i);
        } else {
            factors.push_back(i);
            factors.push_back(N / i);
        }
    }
    sort(factors.begin(), factors.end());
    ll cgcd = 0;
    for (auto i : factors) {
        cgcd = __gcd(cgcd, i);
    }
    if (cgcd != 1) {
        cout << "NO" << endl;
        return 0;
    }
    for (auto i : factors) {
        if (__gcd(i, N / i) == 1) {
            ll x = i, y = N / i;
            ll a, b;
            egcd(x, y, a, b);
            a *= (N - 1);
            b *= (N - 1);
            if (b < 0) {
                swap(a, b);
                swap(x, y);
            }
            ll bmul = (lcm(x, y) / y);
            ll amul = (lcm(x, y) / x);
            ll mul = abs(a / amul) + 1;
            a += mul * amul;
            b -= mul * bmul;
            cout << "YES" << endl;
            cout << 2 << endl;
            cout << a << ' ' << y << endl;
            cout << b << ' ' << x << endl;
            return 0;
        }
    }
    assert(false);
}