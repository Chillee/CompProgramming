#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5e5 + 5;
int N;
vector<int> adj[MAXN];
int dist[MAXN];
int dfs(int cur, int prv = -1, int d = 0) {
    dist[cur] = d;
    int mx = cur;
    for (auto i : adj[cur]) {
        if (i == prv)
            continue;
        int res = dfs(i, cur, d + 1);
        if (dist[res] > dist[mx])
            mx = res;
    }
    return mx;
}
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
    }
    cout << dist[dfs(dfs(0))] << endl;
}