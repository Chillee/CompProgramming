#include <bits/stdc++.h>

using namespace std;
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
int N, M, P;

const int MAXN = 1e5 + 5;

struct PushRelabel {
    typedef ll Flow;
    struct Edge {
        int dest, back;
        Flow f, c;
    };

    vector<vector<Edge>> g;
    vector<Flow> ec;
    vector<Edge *> cur;
    vector<vi> hs;
    vi H;
    PushRelabel(int n) : g(n), ec(n), cur(n), hs(2 * n), H(n) {}

    void addEdge(int s, int t, Flow cap, Flow rcap = 0) {
        if (s == t)
            return;
        Edge a = {t, sz(g[t]), 0, cap};
        Edge b = {s, sz(g[s]), 0, rcap};
        g[s].push_back(a);
        g[t].push_back(b);
    }

    void add_flow(Edge &e, Flow f) {
        Edge &back = g[e.dest][e.back];
        if (!ec[e.dest] && f)
            hs[H[e.dest]].push_back(e.dest);
        e.f += f;
        e.c -= f;
        ec[e.dest] += f;
        back.f -= f;
        back.c += f;
        ec[back.dest] -= f;
    }
    Flow maxflow(int s, int t) {
        int v = sz(g);
        H[s] = v;
        ec[t] = 1;
        vi co(2 * v);
        co[0] = v - 1;
        rep(i, 0, v) cur[i] = g[i].data();
        trav(e, g[s]) add_flow(e, e.c);

        for (int hi = 0;;) {
            while (hs[hi].empty())
                if (!hi--)
                    return -ec[s];
            int u = hs[hi].back();
            hs[hi].pop_back();
            while (ec[u] > 0) // discharge u
                if (cur[u] == g[u].data() + sz(g[u])) {
                    H[u] = 1e9;
                    trav(e, g[u]) if (e.c && H[u] > H[e.dest] + 1) H[u] = H[e.dest] + 1, cur[u] = &e;
                    if (++co[H[u]], !--co[hi] && hi < v)
                        rep(i, 0, v) if (hi < H[i] && H[i] < v)-- co[H[i]], H[i] = v + 1;
                    hi = H[u];
                } else if (cur[u]->c && H[u] == H[cur[u]->dest] + 1)
                    add_flow(*cur[u], min(ec[u], cur[u]->c));
                else
                    ++cur[u];
        }
    }
};
template <int MAXV, class T = int> struct Dinic {
    const static bool SCALING = false; // non-scaling = V^2E, Scaling=VElog(U) with higher constant
    int lim = 1;
    const T INF = numeric_limits<T>::max();
    struct edge {
        int to, rev;
        T cap, flow;
    };
    int s = MAXV - 2, t = MAXV - 1;

    int level[MAXV], ptr[MAXV];
    vector<edge> adj[MAXV];
    void addEdge(int a, int b, T cap, bool isDirected = true) {
        adj[a].push_back({b, adj[b].size(), cap, 0});
        adj[b].push_back({a, adj[a].size() - 1, isDirected ? 0 : cap, 0});
    }
    bool bfs() {
        queue<int> q({s});
        fill(all(level), -1);
        level[s] = 0;
        while (!q.empty() && level[t] == -1) {
            int v = q.front();
            q.pop();
            for (auto e : adj[v]) {
                if (level[e.to] == -1 && e.flow < e.cap && (!SCALING || e.cap - e.flow >= lim)) {
                    q.push(e.to);
                    level[e.to] = level[v] + 1;
                }
            }
        }
        return level[t] != -1;
    }
    T dfs(int v, T flow) {
        if (v == t || !flow)
            return flow;
        for (; ptr[v] < adj[v].size(); ptr[v]++) {
            edge &e = adj[v][ptr[v]];
            if (level[e.to] != level[v] + 1)
                continue;
            if (T pushed = dfs(e.to, min(flow, e.cap - e.flow))) {
                e.flow += pushed;
                adj[e.to][e.rev].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }
    long long calc() {
        long long flow = 0;
        for (lim = SCALING ? (1 << 30) : 1; lim > 0; lim >>= 1) {
            while (bfs()) {
                fill(all(ptr), 0);
                while (T pushed = dfs(s, INF))
                    flow += pushed;
            }
        }
        return flow;
    }
};
Dinic<MAXN> flow;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {

        cin >> N;
        M = N;

        // PushRelabel flow(N + M + 5);
        for (int i = 0; i < N; i++)
            flow.addEdge(0, i + 2, 1);
        for (int i = 0; i < M; i++)
            flow.addEdge(N + i + 2, 1, 1);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                char t;
                cin >> t;
                if (t == '1')
                    flow.addEdge(i + 2, 2 + N + j, 1);
            }
        }
        flow.s = 0, flow.t = 1;
        cout << (flow.calc() % 2 == 1 ? "Odd" : "Even") << endl;
    }
}