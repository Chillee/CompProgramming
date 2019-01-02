#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MOD = 1e9 + 7;
const ll MAXN = 1e4 + 5;
ll T, N;
ll A[MAXN];
ll binExp(ll base, ll exp) {
    if (exp == 0)
        return 1;
    return binExp(base * base % MOD, exp / 2) * (exp % 2 == 1 ? base : 1) % MOD;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (ll t = 0; t < T; t++) {
        cin >> N;
        for (ll i = 0; i < N; i++)
            cin >> A[i];
        ll ans = 0;
        for (ll i = 0; i < N; i++) {
            ans += binExp(2, i) * A[i];
            ans %= MOD;
        }
        for (ll i = 0; i < N; i++) {
            ans -= binExp(2, i) * A[N - i - 1];
            ans = ((ans % MOD) + MOD) % MOD;
        }
        cout << "Case #" << t + 1 << ": " << ans << endl;
    }
}