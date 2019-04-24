#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MOD = 1e9 + 7;
ll N;
ll bin_exp(ll base, ll pow) {
    if (pow == 0)
        return 1;
    return bin_exp(base * base % MOD, pow / 2) * (pow & 1 ? base : 1) % MOD;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (ll i = 0; i < N; i++) {
        ll a, b;
        cin >> a >> b;
        cout << bin_exp(a, b) << endl;
    }
}