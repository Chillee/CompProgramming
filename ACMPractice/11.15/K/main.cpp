#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;
struct Dinic {
    const static int MAXV = 4 * MAXN + 5;
    const int OFFSET = MAXN * 2;
    const int INF = 1e9 + 5;
    struct edge {
        int to, rev, cap, flow;
    };
    const static int source = MAXV - 2;
    const static int sink = MAXV - 1;

    int d[MAXV], ptr[MAXV];
    vector<edge> adj[MAXV];

    void addEdge(int a, int b, int cap, int rcap = -1) {
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
Dinic flow;
int N, M;
int W[MAXN], L[MAXN];
array<int, 2> T[MAXN];
int par[MAXN];
vector<int> ans[MAXN];
vector<int> dfs(int cur) {
    if (cur == flow.source) {
        return {};
    }
    for (auto i : flow.adj[cur]) {
        if (i.flow == -1) {

            i.flow = 0;
            auto res = dfs(i.to);
            if (cur < N) {
                // par[cur] = i.to - flow.OFFSET - 2;
                res.insert(res.begin(), cur);
            }
            return res;
        }
    }
    assert(false);
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    fill(begin(par), end(par), -1);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> W[i] >> L[i];
    }
    cin >> M;
    for (int i = 0; i < M; i++) {
        int a;
        cin >> a;
        T[i] = {a, i};
    }
    // sort(T, T + M);
    for (int i = 0; i < N; i++) {
        if (W[i] == 0)
            flow.addEdge(flow.source, i, 1);
    }
    for (int i = 0; i < N; i++) {
        flow.addEdge(i, i + flow.OFFSET, 1, 0);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j)
                continue;
            if (L[i] >= W[j]) {
                flow.addEdge(i + flow.OFFSET, j, 1, 0);
            }
        }
        for (int j = 0; j < M; j++) {
            if (L[i] >= T[j][0]) {
                flow.addEdge(i + flow.OFFSET, N + j, 1, 0);
            }
        }
    }
    for (int i = 0; i < M; i++) {
        flow.addEdge(N + i, flow.sink, 1);
    }
    int res = flow.calc();
    // cout << res << endl;
    if (res < M) {
        cout << "impossible" << endl;
    } else {
        for (int i = 0; i < M; i++) {
            int cur = N + i;
            auto res = dfs(cur);
            reverse(res.begin(), res.end());
            for (auto i : res) {
                cout << i + 1 << ' ';
            }
            cout << endl;
        }
    }
}