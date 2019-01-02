#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
int T, N, M;
vector<array<int, 2>> adj[MAXN];
bool vis[MAXN];
bool eparity[MAXN];
bool parity[MAXN];
bool dfs(int cur) {
    if (vis[cur])
        return false;
    vis[cur] = true;
    for (auto i : adj[cur]) {
        bool res = dfs(i[0]);
        if (res)
            eparity[i[1]] = !eparity[i[1]];

        parity[cur] ^= res;
    }
    return parity[cur];
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int t = 0; t < T; t++) {
        fill(begin(vis), end(vis), false);
        fill(begin(parity), end(parity), 0);
        fill(begin(eparity), end(eparity), 0);
        fill(begin(adj), end(adj), vector<array<int, 2>>());
        cin >> N >> M;
        for (int i = 0; i < M; i++) {
            int a, b;
            cin >> a >> b;
            a--, b--;
            adj[a].push_back({b, i});
            parity[b] = !parity[b];
            adj[b].push_back({a, i});
        }
        if (M % 2 == 1) {
            cout << -1 << endl;
            continue;
        }
        dfs(0);
        for (int i = 0; i < M; i++) {
            cout << eparity[i] << " ";
        }
        cout << endl;
    }
}