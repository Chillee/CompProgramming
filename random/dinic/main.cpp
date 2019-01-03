#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll N, M;

const ll MAXN = 5005;

inline void scan_ull(ll *p) {
    static char c;
    while ((c = getchar_unlocked()) < '0')
        ; // just to be safe
    for (*p = c - '0'; (c = getchar_unlocked()) >= '0'; *p = *p * 10 + c - '0')
        ;
}

const ll INF = 1e9 + 5;
struct Dinic {
    const static ll MAXV = MAXN;
    const ll INF = 1e9 + 5;
    struct edge {
        ll to, rev, cap, flow;
    };
    ll s = MAXV - 2;
    ll t = MAXV - 1;

    ll d[MAXV], ptr[MAXV];
    vector<edge> adj[MAXV];

    void addEdge(ll a, ll b, ll cap, ll rcap = -1) {
        adj[a].push_back({b, adj[b].size(), cap, 0});
        if (rcap == -1)
            rcap = cap;
        adj[b].push_back({a, adj[a].size() - 1, rcap, 0});
    }

    bool bfs() {
        queue<ll> q({s});
        fill(begin(d), end(d), -1);
        d[s] = 0;
        while (!q.empty() && d[t] == -1) {
            ll v = q.front();
            q.pop();
            for (auto e : adj[v]) {
                if (d[e.to] == -1 && e.flow < e.cap) {
                    q.push(e.to);
                    d[e.to] = d[v] + 1;
                }
            }
        }
        return d[t] != -1;
    }

    ll dfs(ll v, ll flow) {
        if (v == t || !flow)
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
            while (ll pushed = dfs(s, INF))
                flow += pushed;
        }
        return flow;
    }
};
Dinic dinic;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // cin >> N >> M;
    scan_ull(&N);
    scan_ull(&M);
    for (ll i = 0; i < M; i++) {
        ll a, b, d;
        scan_ull(&a), scan_ull(&b), scan_ull(&d);
        // cin >> a >> b >> d;
        a--, b--;
        dinic.addEdge(a, b, d);
    }
    dinic.s = 0;
    dinic.t = N - 1;
    cout << dinic.calc() << endl;
}