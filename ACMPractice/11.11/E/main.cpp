#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 35;
ll N, M, C;
char grid[MAXN][MAXN];
ll cost[30];
struct Dinic {
    const static ll MAXV = MAXN * MAXN * 5;
    const ll INF = 1e9 + 5;
    struct edge {
        ll to, rev, cap, flow;
    };
    ll source = 0;
    ll sink = 1;

    ll d[MAXV], ptr[MAXV];
    vector<edge> adj[MAXV];

    void add_edge(ll a, ll b, ll cap, ll rcap = -1) {
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
            ll v = q.front();
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

    ll dfs(ll v, ll flow) {
        if (v == sink || !flow)
            return flow;
        for (; ptr[v] < adj[v].size(); ptr[v]++) {
            edge &e = adj[v][ptr[v]];
            if (d[e.to] != d[v] + 1)
                continue;
            if (ll pushed = dfs(e.to, min(flow, e.cap - e.flow))) {
                e.flow += pushed;
                adj[e.to][e.rev].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }

    ll calc() {
        ll flow = 0;
        while (bfs()) {
            fill(begin(ptr), end(ptr), 0);
            while (ll pushed = dfs(source, INF))
                flow += pushed;
        }
        return flow;
    }
};
Dinic dinic;
bool isValid(ll r, ll c) { return r >= 0 && c >= 0 && r < M && c < N; }
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M >> C;
    ll source;
    for (ll i = 0; i < M; i++) {
        for (ll j = 0; j < N; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'B')
                source = i * N + j;
        }
    }
    for (ll i = 0; i < C; i++)
        cin >> cost[i];

    dinic.source = source;
    dinic.sink = 3 * M * N;
    ll offset = M * N;
    ll INF = 1e9 + 5;
    vector<array<ll, 2>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    for (ll i = 0; i < M; i++) {
        for (ll j = 0; j < N; j++) {
            bool isBorder = false;
            ll outNode = i * N + j + offset;
            if (grid[i][j] == '.') {
                dinic.add_edge(i * N + j, i * N + j + offset, INF, 0);
            } else if (grid[i][j] == 'B') {
                outNode = dinic.source;
            } else {
                dinic.add_edge(i * N + j, i * N + j + offset, cost[grid[i][j] - 'a'], 0);
            }
            for (auto dir : dirs) {
                ll cr = i + dir[0], cc = j + dir[1];
                ll curn = cr * N + cc;
                if (isValid(cr, cc)) {
                    dinic.add_edge(outNode, curn, INF, 0);
                } else {
                    isBorder = true;
                }
            }
            if (isBorder) {
                dinic.add_edge(outNode, dinic.sink, INF, 0);
            }
        }
    }
    ll res = dinic.calc();
    if (res >= INF) {
        cout << -1 << endl;
    } else {
        cout << res << endl;
    }
}