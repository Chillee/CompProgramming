#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
typedef long long ll;
using namespace std;

ll blocksNeeded(ll x) { return (x * (x + 1)) / 2; }
const ll MOD = 1e9 + 7;
const ll MAXN = 2e5 + 5;
ll dp[2][MAXN];
ll R, G;
ll numBlocks(ll x) { return x * (x + 1) / 2; }
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> R >> G;
    dp[0][0] = 1;
    ll H = 0;
    for (; H < 1000; H++) {
        if (H * (H + 1) / 2 > R + G)
            break;
    }
    for (ll i = 1; i < H; i++) {
        for (ll j = 0; j <= min(i * (i + 1) / 2, R); j++) {
            dp[1][j] = 0;
            if (j >= i * (i + 1) / 2 - G && j<=(i-1)*i/2)
                dp[1][j] += dp[0][j];
            if (j >= i)
                dp[1][j] += dp[0][j - i];
            dp[1][j] %= MOD;
        }
        for (ll j = 0; j <= R; j++)
            dp[0][j] = dp[1][j];
    }
    ll ans = 0;
    for (ll i = 0; i <= R; i++) {
        ans += dp[0][i];
        ans %= MOD;
    }
    cout << ans << endl;
}