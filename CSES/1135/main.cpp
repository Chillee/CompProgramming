#pragma GCC optimize("O3")
#include <bits/stdc++.h>

#define all(x) x.begin(), x.end()
using namespace std;

template <int MAXN> struct LCA { // O(1) queries
    const static int MAXB = 33 - __builtin_clz(MAXN);
    int tim[MAXN], depth[MAXN];
    array<int, 2> st[MAXN * 2][MAXB];
    vector<array<int, 2>> euler;
    void calc(vector<int> adj[], int cur = 0, int p = 0, int d = 0) {
        depth[cur] = d;
        tim[cur] = euler.size();
        euler.push_back({d, cur});
        for (auto i : adj[cur]) {
            if (i == p)
                continue;
            calc(adj, i, cur, d + 1);
            euler.push_back({d, cur});
        }
        if (p == cur) {
            for (int i = 0; i < euler.size(); i++)
                st[i][0] = euler[i];
            for (int j = 1; j <= MAXB; j++)
                for (int i = 0; i + (1 << j) <= euler.size(); i++)
                    st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
    int query(int a, int b) {
        if (a == b)
            return a;
        if ((a = tim[a]) > (b = tim[b]))
            swap(a, b);
        int k = 31 - __builtin_clz(b - a);
        return min(st[a][k], st[b - (1 << k)][k])[1];
    }
    int dist(int a, int b) {
        int lca = query(a, b);
        return depth[a] + depth[b] - 2 * depth[lca];
    }
};
const int MAXN = 2e5 + 5;
int N, Q;
vector<int> adj[MAXN];
LCA<MAXN> lca;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> Q;
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    lca.calc(adj);
    for (int i = 0; i < Q; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        cout << lca.dist(a, b) << endl;
    }
}