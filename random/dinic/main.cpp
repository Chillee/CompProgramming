#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, M;

const ll MAXN = 5005;

inline void scan_uint(int *p) {
    static char c;
    while ((c = getchar_unlocked()) < '0')
        ; // just to be safe
    for (*p = c - '0'; (c = getchar_unlocked()) >= '0'; *p = *p * 10 + c - '0')
        ;
}

const ll INF = 1e9 + 5;
ll lim;

struct edge {
    ll to, rev, cap, flow;
};

ll source, sink, d[MAXN], ptr[MAXN];
vector<edge> adj[MAXN];

void add_edge(ll a, ll b, ll cap, ll rcap = -1) {
    adj[a].push_back({b, adj[b].size(), cap, 0});
    if (rcap == -1)
        rcap = cap;
    adj[b].push_back({a, adj[a].size() - 1, rcap, 0});
}

bool bfs() {
    queue<ll> q;
    q.push(source);
    fill(begin(d), end(d), -1);
    d[source] = 0;
    while (!q.empty() && d[sink] == -1) {
        ll v = q.front();
        q.pop();
        for (auto e : adj[v]) {
            if (d[e.to] == -1 && e.flow < e.cap && e.cap - e.flow >= lim) {
                q.push(e.to);
                d[e.to] = d[v] + 1;
            }
        }
    }
    return d[sink] != -1;
}

ll dfs(ll v, ll flow) {
    if (!flow)
        return 0;
    if (v == sink)
        return flow;
    for (; ptr[v] < adj[v].size(); ++ptr[v]) {
        edge &e = adj[v][ptr[v]];
        if (d[e.to] != d[v] + 1 || !(e.cap - e.flow >= lim))
            continue;
        ll pushed = dfs(e.to, min(flow, e.cap - e.flow));
        if (pushed) {
            e.flow += pushed;
            adj[e.to][e.rev].flow -= pushed;
            return pushed;
        }
    }
    return 0;
}

ll dinic() {
    ll flow = 0;
    for (lim = 1 << 30; lim > 0; lim >>= 1)
        while (bfs()) {
            fill(begin(ptr), end(ptr), 0);
            while (ll pushed = dfs(source, lim))
                flow += pushed;
        }
    return flow;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // cin >> N >> M;
    scan_uint(&N);
    scan_uint(&M);
    for (ll i = 0; i < M; i++) {
        int a, b, d;
        scan_uint(&a), scan_uint(&b), scan_uint(&d);
        // cin >> a >> b >> d;
        a--, b--;
        add_edge(a, b, d);
        // adjmat[a][b] += d;
        // adjmat[b][a] += d;
    }
    // for (ll i = 0; i < N; i++) {
    //     for (ll j = i; j < N; j++) {
    //         if (i == j)
    //             continue;
    //         if (adjmat[i][j] > 0 || adjmat[j][i] > 0) {
    //         }
    //     }
    // }
    source = 0, sink = N - 1;
    cout << dinic() << endl;
}