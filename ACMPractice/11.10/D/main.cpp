#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 105;
const ll MAXG = 2e5 + 5;
const ll INF = 1e14;
struct gig {
    ll s, e, v, m;
    bool operator<(gig x) { return make_tuple(e, s, v, m) < make_tuple(x.e, x.s, x.v, x.m); }
};

ll G, K, R;
ll adj[MAXN][MAXN];
ll dp[MAXN][MAXG];
vector<gig> gigs;
vector<ll> endTimes;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (ll i = 0; i < MAXN; i++)
        fill(dp[i], dp[i] + MAXG, -INF);
    for (ll i = 0; i < MAXN; i++)
        for (ll j = 0; j < MAXN; j++) {
            if (i != j)
                adj[i][j] = INF;
        }

    cin >> G >> K >> R;
    for (ll i = 0; i < R; i++) {
        ll a, b, d;
        cin >> a >> b >> d;
        a--, b--;
        adj[a][b] = d;
        adj[b][a] = d;
    }
    for (ll i = 0; i < K; i++) {
        for (ll j = 0; j < K; j++) {
            for (ll k = 0; k < K; k++) {
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
            }
        }
    }
    for (ll i = 0; i < G; i++) {
        ll v, s, e, m;
        cin >> v >> s >> e >> m;
        v--;
        gigs.push_back({s, e, v, m});
    }
    gigs.push_back({0, 0, 0, 0});
    sort(gigs.begin(), gigs.end());
    for (auto i : gigs)
        endTimes.push_back(i.e);

    dp[0][0] = 0;
    for (ll i = 1; i < gigs.size(); i++) {
        auto g = gigs[i];
        ll cur = -INF;
        for (ll j = 0; j < K; j++) {
            ll idx = upper_bound(endTimes.begin(), endTimes.end(), g.s - adj[j][g.v]) - endTimes.begin() - 1;
            if (idx < 0 || idx >= i)
                continue;
            cur = max(cur, dp[j][idx] + g.m);
        }
        dp[g.v][i] = cur;
        for (ll j = 0; j < K; j++) {
            dp[j][i] = max(dp[j][i], dp[j][i - 1]);
        }
    }
    ll ans = 0;
    for (ll i = 0; i < K; i++) {
        ans = max(ans, dp[i][gigs.size() - 1]);
    }
    cout << ans << endl;
}