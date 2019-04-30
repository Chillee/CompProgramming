#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

template <int MAXV, class T = int> struct Dinic {
    const T INF = numeric_limits<T>::max();
    struct edge {
        int to, rev;
        T c, f;
    };
    int s, t;
    vi lvl, ptr;
    vector<vector<edge>> adj;
    Dinic(int n) : lvl(n), ptr(n), adj(n) {}
    void addEdge(int a, int b, T c, int rcap = 0) {
        adj[a].push_back({b, sz(adj[b]), c, 0});
        adj[b].push_back({a, sz(adj[a]) - 1, rcap, 0});
    }
    bool bfs() {
        queue<int> q({s});
        fill(all(lvl), -1);
        lvl[s] = 0;
        while (!q.empty() && lvl[t] == -1) {
            int v = q.front();
            q.pop();
            trav(e, adj[v]) {
                if (lvl[e.to] == -1 && e.f < e.c)
                    q.push(e.to), lvl[e.to] = lvl[v] + 1;
            }
        }
        return lvl[t] != -1;
    }
    T dfs(int v, T f) {
        if (v == t || !f) return f;
        for (; ptr[v] < adj[v].size(); ptr[v]++) {
            edge &e = adj[v][ptr[v]];
            if (lvl[e.to] != lvl[v] + 1) continue;
            if (T p = dfs(e.to, min(f, e.c - e.f))) {
                e.f += p, adj[e.to][e.rev].f -= p;
                return p;
            }
        }
        return 0;
    }
    ll calc(int _s, int _t) {
        s = _s, t = _t;
        ll flow = 0;
        while (bfs()) {
            fill(all(ptr), 0);
            while (T pushed = dfs(s, INF))
                flow += pushed;
        }
        return flow;
    }
};

const int MAXN = 1e5 + 5;
void SPOJMATCHING() {
    int N, M, P;
    cin >> N >> M >> P;
    Dinic<MAXN> flow(N + M + 2);
    for (int i = 0; i < N; i++)
        flow.addEdge(0, 2 + i, 1);
    for (int i = 0; i < M; i++)
        flow.addEdge(2 + N + i, 1, 1);
    for (ll i = 0; i < P; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        flow.addEdge(2 + a, 2 + b + N, 1);
    }
    cout << flow.calc(0, 1) << endl;
}
void LOJ() {
    int N, M, S, T;
    cin >> N >> M >> S >> T;
    S--, T--;
    Dinic<MAXN> flow(N);
    for (int i = 0; i < M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        flow.addEdge(a, b, c);
    }
    cout << flow.calc(S, T) << endl;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    SPOJMATCHING();
    // LOJ();
}