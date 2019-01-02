#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
int N;
double S;
vector<int> adj[MAXN];
int dfs(int cur, int p) {
    if (adj[cur].size() == 1 && adj[cur][0] == p)
        return 1;
    int sm = 0;
    for (auto i : adj[cur]) {
        if (i != p)
            sm += dfs(i, cur);
    }
    return sm;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> S;
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 0; i < N; i++) {
        if (adj[i].size() > 1) {
            int res = dfs(i, i);
            cout << fixed << setprecision(20) << (S / res) * 2 << endl;
            return 0;
        }
    }
    cout << S << endl;
    return 0;
}