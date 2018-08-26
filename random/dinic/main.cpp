#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 5005;
const ll INF = 1e18;

struct edge {
    ll a, b, cap, flow;
};

ll N, M;
ll S, T, d[MAXN], ptr[MAXN], q[MAXN];
vector<edge> e;
vector<ll> g[MAXN];

void add_edge(ll a, ll b, ll cap) {
    edge e1 = {a, b, cap, 0};
    g[a].push_back(e.size());
    e.push_back(e1);
}

bool bfs() {
    ll qh = 0, qt = 0;
    q[qt++] = S;
    fill(d, d + N, -1);
    d[S] = 0;
    while (qh < qt && d[T] == -1) {
        ll v = q[qh++];
        for (ll i = 0; i < g[v].size(); ++i) {
            ll id = g[v][i], to = e[id].b;
            if (d[to] == -1 && e[id].flow < e[id].cap) {
                q[qt++] = to;
                d[to] = d[v] + 1;
            }
        }
    }
    return d[T] != -1;
}

ll dfs(ll v, ll flow) {
    if (!flow)
        return 0;
    if (v == T)
        return flow;
    for (; ptr[v] < (ll)g[v].size(); ++ptr[v]) {
        ll id = g[v][ptr[v]], to = e[id].b;
        if (d[to] != d[v] + 1)
            continue;
        ll pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
        if (pushed) {
            e[id].flow += pushed;
            e[id ^ 1].flow -= pushed;
            return pushed;
        }
    }
    return 0;
}

ll dinic() {
    ll flow = 0;
    while (true) {
        if (!bfs())
            break;
        fill(ptr, ptr + N, 0);
        while (ll pushed = dfs(S, INF))
            flow += pushed;
    }
    return flow;
}
ll adj[MAXN][MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for (ll i = 0; i < M; i++) {
        ll a, b, d;
        cin >> a >> b >> d;
        a--, b--;
        adj[a][b] += d;
        adj[b][a] += d;
    }
    for (ll i = 0; i < N; i++) {
        for (ll j = i; j < N; j++) {
            if (i == j)
                continue;
            if (adj[i][j] > 0 || adj[j][i] > 0) {
                add_edge(j, i, adj[j][i]);
                add_edge(i, j, adj[i][j]);
            }
        }
    }
    S = 0, T = N - 1;
    cout << dinic() << endl;
}