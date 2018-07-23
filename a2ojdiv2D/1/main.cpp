#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll MAXN = 1e5 + 5;
const ll MOD = 1e9 + 7;
ll T, K, A, B;
ll dp[MAXN];
ll sums[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T >> K;
    dp[0] = 1;
    for (ll i = 1; i < MAXN; i++) {
        dp[i] = dp[i - 1];
        if (i - K >= 0) {
            dp[i] = (dp[i] + dp[i - K]) % MOD;
        }
    }
    sums[0] = dp[0];
    for (ll i = 1; i < MAXN; i++) {
        sums[i] = (sums[i - 1] + dp[i]) % MOD;
    }

    for (ll t = 0; t < T; t++) {
        ll a, b;
        cin >> a >> b;
        cout << (sums[b] - sums[a - 1] + MOD) % MOD << endl;
    }
}