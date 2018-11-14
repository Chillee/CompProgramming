#include <bits/stdc++.h>

using namespace std;

const int MAXN = 205;
int N;
vector<int> adj[MAXN];
int dist[MAXN];
void dfs(int cur, pair<int, int> removed, int d) {
    if (dist[cur] != -1)
        return;
    dist[cur] = d;
    for (auto i : adj[cur]) {
        if (removed == make_pair(i, cur) || removed == make_pair(cur, i))
            continue;

        dfs(i, removed, d + 1);
    }
}
int getBiggest(int cur, pair<int, int> removed) {
    fill(dist, dist + MAXN, -1);
    dfs(cur, removed, 0);
    int mx = 0;
    for (int i = 0; i < N; i++) {
        if (dist[i] > dist[mx])
            mx = i;
    }
    fill(dist, dist + MAXN, -1);
    dfs(mx, removed, 0);
    int res = 0;
    for (int i = 0; i < N; i++)
        res = max(res, dist[i]);
    return res;
}

vector<pair<int, int>> edges;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
        edges.push_back({a, b});
    }
    int ans = 0;
    for (auto e : edges) {
        int p1 = getBiggest(e.first, e);
        int p2 = getBiggest(e.second, e);
        // cout << e.first << ' ' << e.second << ' ' << p1 << ' ' << p2 << endl;
        ans = max(ans, p1 * p2);
    }
    cout << ans << endl;
}