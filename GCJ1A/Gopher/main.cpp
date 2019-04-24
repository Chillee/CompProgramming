#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll euclid(ll a, ll b, ll &x, ll &y) {
    if (b) {
        ll d = euclid(b, a % b, y, x);
        return y -= a / b * x, d;
    }
    return x = 1, y = 0, a;
}
ll chinese(ll a, ll m, ll b, ll n) {
    ll x, y;
    euclid(m, n, x, y);
    ll ret = a * (y + m) % m * n + b * (x + n) % n * m;
    if (ret >= m * n)
        ret -= m * n;
    return ret;
}

ll chinese_common(ll a, ll m, ll b, ll n) {
    ll d = __gcd(m, n);
    if (((b -= a) %= n) < 0)
        b += n;
    if (b % d)
        return -1; // No solution
    return d * chinese(ll(0), m / d, b / d, n / d) + a;
}
ll T, N, M;
signed main() {
    // ios::sync_with_stdio(0);
    // cin.tie(0);
    cin >> T >> N >> M;
    for (ll t = 0; t < T; t++) {
        vector<ll> primes = {5, 7, 11, 13, 17, 18};
        vector<ll> pars;
        for (auto p : primes) {
            for (ll i = 0; i < 18; i++)
                cout << p << ' ';
            cout << endl << flush;
            ll ans = 0;
            for (ll i = 0; i < 18; i++) {
                ll p;
                cin >> p;
                ans += p;
            }
            pars.push_back(ans % p);
        }
        ll curAns = 0;
        ll curP = 1;
        for (ll i = 0; i < primes.size(); i++) {
            curAns = chinese_common(curAns, curP, pars[i], primes[i]);
            curP *= primes[i];
        }
        cout << curAns << endl << flush;
        int verdict;
        cin >> verdict;
        if (verdict == -1)
            exit(0);
    }
}