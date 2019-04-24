#pragma GCC optimize("O3")
#include <bits/stdc++.h>

#define all(x) x.begin(), x.end()
using namespace std;

typedef long long ll;
const ll MAXN = 5e5 + 5;
vector<ll> adj[MAXN];
ll N;
ll stSize[MAXN];
ll dfs(ll cur, ll p = -1) {
    stSize[cur] = 1;
    ll ans = 0;
    for (auto i : adj[cur]) {
        if (i == p)
            continue;
        ll cnt = dfs(i, cur);
        stSize[cur] += stSize[i];
        ans += (cnt + stSize[i]);
    }
    return ans;
}
ll ans[MAXN];
void dfs2(ll cur, ll cAns, ll p = -1) {
    ans[cur] = cAns;
    for (auto i : adj[cur]) {
        if (i == p)
            continue;
        dfs2(i, cAns - stSize[i] + (N - stSize[i]), cur);
    }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (ll i = 0; i < N - 1; i++) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    ll res = dfs(0);
    dfs2(0, res);
    for (ll i = 0; i < N; i++)
        cout << ans[i] << ' ';
    cout << endl;
}