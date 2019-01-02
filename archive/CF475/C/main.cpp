#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MOD = 1e9 + 9;

typedef long long ll;
ll N, A, B, K;

ll bin_exp(ll base, ll exp) {
    if (exp == 0)
        return 1;
    return (bin_exp(base * base % MOD, exp / 2) * (exp % 2 == 1 ? base : 1) + MOD) % MOD;
}

ll mod_inv(ll a) { return bin_exp(a, MOD - 2); }

ll umod(ll x) { return (x % MOD + MOD) % MOD; }

int main() {
    cin >> N >> A >> B >> K;
    ll sumTerm = 0;
    for (ll i = 0; i < K; i++) {
        char c;
        cin >> c;
        if (c == '+') {
            sumTerm = umod(sumTerm + bin_exp(A, N - i) * bin_exp(B, i));
        } else {
            sumTerm = umod(sumTerm - bin_exp(A, N - i) * bin_exp(B, i));
        }
        // cout << sumTerm << endl;
    }
    // sumTerm = 450246164;
    ll frac = umod(bin_exp(umod(B * mod_inv(A)), K));
    if (frac == 1) {
        cout << umod((N + 1) / K * sumTerm) << endl;
        return 0;
    }
    ll fracTerm = umod(umod(1 - bin_exp(frac, (N + 1) / K)) * umod(mod_inv(1 - frac)));
    ll res = umod(fracTerm * sumTerm);
    cout << res << endl;
}