#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
int N;
vector<int> adjlist[MAXN];
vector<int> children[MAXN];
bool vis[MAXN];
int depth[MAXN];
bool root(int cur, int curDepth) {
    if (vis[cur])
        return false;
    vis[cur] = true;
    depth[cur] = curDepth;
    for (auto i : adjlist[cur]) {
        if (root(i, curDepth + 1))
            children[cur].push_back(i);
    }
    return true;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adjlist[a].push_back(b);
        adjlist[b].push_back(a);
    }
    root(0, 1);
    double ans = 0;
    for (int i = 0; i < N; i++) {
        ans += 1.0 / depth[i];
    }
    cout << setprecision(15) << ans << endl;
}