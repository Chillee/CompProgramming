#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

typedef long long ll;
const ll MAXN = 1e6 + 5;
const ll MOD = 1e9 + 7;
ll T;
ll dp[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    dp[0] = 1;
    for (ll i = 1; i < MAXN; i++) {
        for (ll j = max(0LL, i - 8); j < i; j++) {
            dp[i] = (dp[i] + dp[j]) % MOD;
        }
    }
    cin >> T;
    for (ll t = 0; t < T; t++) {
        ll N;
        cin >> N;
        cout << dp[N / 3] << endl;
    }
    // for (ll i = 0; i < 25; i++) {
    //     cout << dp[i] << ' ';
    // }
    // cout << endl;
}