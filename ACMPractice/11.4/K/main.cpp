#include <bits/stdc++.h>

using namespace std;

const int MAXN = 22;
struct Dinic {
    const static int MAXV = MAXN;
    const int INF = 1e9 + 5;
    struct edge {
        int to, rev, cap, flow;
    };
    const static int source = 0;
    const static int sink = 1;

    int d[MAXV], ptr[MAXV];
    vector<edge> adj[MAXV];

    void add_edge(int a, int b, int cap, int rcap = -1) {
        adj[a].push_back({b, adj[b].size(), cap, 0});
        if (rcap == -1)
            rcap = cap;
        adj[b].push_back({a, adj[a].size() - 1, rcap, 0});
    }

    bool bfs() {
        queue<int> q({source});
        fill(begin(d), end(d), -1);
        d[source] = 0;
        while (!q.empty() && d[sink] == -1) {
            int v = q.front();
            q.pop();
            for (auto e : adj[v]) {
                if (d[e.to] == -1 && e.flow < e.cap) {
                    q.push(e.to);
                    d[e.to] = d[v] + 1;
                }
            }
        }
        return d[sink] != -1;
    }

    int dfs(int v, int flow) {
        if (v == sink || !flow)
            return flow;
        for (; ptr[v] < adj[v].size(); ptr[v]++) {
            edge &e = adj[v][ptr[v]];
            if (d[e.to] != d[v] + 1)
                continue;
            if (int pushed = dfs(e.to, min(flow, e.cap - e.flow))) {
                e.flow += pushed;
                adj[e.to][e.rev].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }

    int calc() {
        int flow = 0;
        while (bfs()) {
            fill(begin(ptr), end(ptr), 0);
            while (int pushed = dfs(source, INF))
                flow += pushed;
        }
        return flow;
    }
};

Dinic dinic;
int R, C;
bool grid[MAXN][MAXN];
bool isValid(int r, int c) { return (r >= 0 && c >= 0 && r < R && c < C); }
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> R >> C;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            char t;
            cin >> t;
            grid[i][j] = (t == '-');
        }
    }
    vector<array<int, 2>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int lft = 0, rght = 0;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (i + j & 1) {
                dinic.add_edge(dinic.source, i * C + j + 2, 1 + grid[i][j]);
                lft += 1 + grid[i][j];
                for (auto dir : dirs) {
                    int nr = i + dir[0];
                    int nc = j + dir[1];
                    if (!isValid(nr, nc))
                        continue;
                    dinic.add_edge(i * C + j + 2, nr * C + nc + 2, 2);
                }
            } else {
                dinic.add_edge(i * C + j + 2, dinic.sink, 1 + grid[i][j]);
                rght += 1 + grid[i][j];
            }
        }
    }
    cout << (dinic.calc() == max(lft, rght) ? "Y" : "N") << endl;
}