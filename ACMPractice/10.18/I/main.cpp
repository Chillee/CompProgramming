#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

typedef long long ll;
const int MAXN = 4005;
int N, M, S;
array<ll, 2> beagles[MAXN / 2];
array<ll, 2> water[MAXN / 2];
int C[MAXN / 2];

const int INF = 1e9 + 5;
struct edge {
    int to, rev, cap, flow;
};
int source, sink, d[MAXN], ptr[MAXN];
vector<edge> adj[MAXN];

void add_edge(int a, int b, int cap, int rcap = -1) {
    adj[a].push_back({b, adj[b].size(), cap, 0});
    if (rcap == -1)
        rcap = cap;
    adj[b].push_back({a, adj[a].size() - 1, rcap, 0});
}

bool bfs() {
    queue<ll> q({source});
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
    if (!flow)
        return 0;
    if (v == sink)
        return flow;
    for (; ptr[v] < adj[v].size(); ++ptr[v]) {
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

int dinic(int s, int t) {
    source = s, sink = t;
    int flow = 0;
    while (bfs()) {
        fill(begin(ptr), end(ptr), 0);
        while (int pushed = dfs(source, INF))
            flow += pushed;
    }
    return flow;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M >> S;
    for (int i = 0; i < N; i++) {
        cin >> beagles[i][0] >> beagles[i][1];
    }
    for (int i = 0; i < M; i++) {
        cin >> water[i][0] >> water[i][1] >> C[i];
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            ll dx = beagles[i][0] - water[j][0];
            ll dy = beagles[i][1] - water[j][1];
            if (sqrt(dx * dx + dy * dy) + 10 <= S) {
                add_edge(2 + i, 2 + N + j, 1, 0);
            }
        }
    }
    for (int i = 0; i < M; i++) {
        add_edge(2 + N + i, 1, C[i], 0);
    }
    for (int i = 0; i < N; i++) {
        add_edge(0, 2 + i, 1, 0);
    }
    // cout << dinic() << endl;
    cout << (dinic(0, 1) == N ? "YES" : "NO") << endl;
}