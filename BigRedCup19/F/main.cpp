#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
typedef long long ll;
using namespace std;

const ll MAXN = 1e5 + 5;
const ll MOD = 1e9 + 7;
vector<ll> g[MAXN];
ll dp[MAXN][12][3];
ll n, m, k;
ll t;
void dfs(ll x, ll p = -1) {
    dp[x][0][0] = k - 1, dp[x][1][1] = 1, dp[x][0][2] = m - k;
    for (ll i = 0; i < g[x].size(); i++) {
        if (g[x][i] == p)
            continue;
        dfs(g[x][i], x);
        ll u = g[x][i];
        ll tmp[12][3] = {0};
        for (ll j = 0; j <= t; j++) {
            for (ll k = t; k >= j; k--) {
                tmp[k][0] += dp[x][k - j][0] * ((dp[u][j][0] + dp[u][j][1] + dp[u][j][2])%MOD);
                tmp[k][0] %= MOD;
                tmp[k][1] += dp[x][k - j][1] * (dp[u][j][0]);
                tmp[k][1] %= MOD;
                tmp[k][2] += dp[x][k - j][2] * ((dp[u][j][0] + dp[u][j][2])%MOD);
                tmp[k][2] %= MOD;
            }
        }
        memcpy(dp[x], tmp, sizeof(tmp));
    }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (ll i = 1; i < n; i++) {
        ll u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    cin >> k >> t;
    dfs(1);
    ll ans = 0;
    for (ll i = 0; i <= t; i++) {
        ans += dp[1][i][0] + dp[1][i][1] + dp[1][i][2];
        ans %= MOD;
    }
    cout << ans << endl;
}