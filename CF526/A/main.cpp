#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 3e5 + 5;
ll N;
vector<array<ll, 2>> adj[MAXN];
bool vis[MAXN];
ll dp[MAXN];
ll W[MAXN];
ll ans = 0;
void calc(ll cur, ll par) {
    dp[cur] = W[cur];
    for (auto i : adj[cur]) {
        if (i[1] != par)
            calc(i[1], cur);
    }

    vector<ll> res;
    for (auto i : adj[cur]) {
        if (i[1] != par)
            res.push_back(dp[i[1]] - i[0]);
    }

    sort(res.begin(), res.end(), greater<ll>());
    if (res.size() == 0) {
        ans = max(ans, dp[cur]);
    } else if (res.size() == 1) {
        dp[cur] = max(dp[cur], dp[cur] + res[0]);
        ans = max(ans, dp[cur]);
    } else if (res.size() >= 2) {
        ll t = 0;
        for (ll i = 0; i < 2; i++) {
            if (res[i] > 0)
                t += res[i];
        }
        ans = max(ans, dp[cur] + t);
        dp[cur] = max(dp[cur], dp[cur] + res[0]);
    }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (ll i = 0; i < N; i++)
        cin >> W[i];
    for (ll i = 0; i < N - 1; i++) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--, v--;
        adj[u].push_back({c, v});
        adj[v].push_back({c, u});
    }
    calc(0, 0);
    // for (ll i = 0; i < N; i++)
    //     cout << dp[i] << ' ';
    // cout << endl;
    cout << ans << endl;
}