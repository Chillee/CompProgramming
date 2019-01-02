#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXB = 200;
const ll MAXK = 1005;
const ll MOD = 1e9 + 9;
ll K, B;
array<ll, 2> dp[MAXB][MAXK];
ll cnt[MAXK];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> K >> B;
    dp[0][0] = {1, 0};
    for (ll i = 0; i < B; i++) {
        for (ll j = 0; j < K; j++) {
            dp[i + 1][(j * 2) % K][0] += dp[i][j][0];
            dp[i + 1][(j * 2) % K][1] += dp[i][j][1];
            dp[i + 1][(j * 2) % K][0] %= MOD;
            dp[i + 1][(j * 2) % K][1] %= MOD;
            dp[i + 1][(j * 2 + 1) % K][0] += dp[i][j][0];
            dp[i + 1][(j * 2 + 1) % K][1] += dp[i][j][1] + dp[i][j][0];
            dp[i + 1][(j * 2 + 1) % K][0] %= MOD;
            dp[i + 1][(j * 2 + 1) % K][1] %= MOD;
        }
    }
    cout << dp[B][0][1] << endl;
}