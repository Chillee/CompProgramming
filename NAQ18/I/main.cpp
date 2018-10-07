#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

const int MAXN = 3e5 + 5;
int N, K, M;
int par[MAXN];
map<int, set<int>> paths;
vector<int> adjlist[MAXN];
bool vis[MAXN];
set<int> roots;
int ans = 0;
void climb(int cur) {
    if (vis[cur])
        return;
    vis[cur] = true;
    if (par[cur] == -1) {
        roots.insert(cur);
    }
    climb(par[cur]);
}
set<int> dfs(int cur) {
    set<int> starts = paths[cur];
    for (auto i : adjlist[cur]) {
        auto t = dfs(i);
        for (auto j : t) {
            starts.insert(j);
        }
    }
    // cout << "cur: " << cur << endl;
    // for (auto i : starts) {
    //     cout << i << ' ';
    // }
    // cout << endl;
    if (starts.find(cur) != starts.end()) {
        ans++;
        starts.clear();
    }
    return starts;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K >> M;
    fill(par, par + N, -1);
    for (int i = 0; i < K; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        par[b] = a;
        adjlist[a].push_back(b);
    }
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        paths[b].insert(a);
    }
    for (int i = 0; i < N; i++) {
        climb(i);
    }
    for (auto i : roots) {
        dfs(i);
    }
    cout << ans << endl;
}