#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5e5 + 5;
int N;
vector<int> adj[MAXN];
int dp[MAXN][2];
void calc(int cur, int prv) {
    if (adj[cur].size() == 1 && adj[cur][0] == prv)
        return;
    for (auto i : adj[cur]) {
        if (i == prv)
            continue;
        calc(i, cur);
    }
    int mx = -1e9 + 5;
    for (auto i : adj[cur]) {
        if (i == prv)
            continue;
        dp[cur][0] += dp[i][1];
        dp[cur][1] += dp[i][1];
        mx = max(dp[i][0] - dp[i][1], mx);
    }
    dp[cur][1] += mx + 1;
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
    calc(0, 0);
    cout << max(dp[0][0], dp[0][1]) << endl;
}