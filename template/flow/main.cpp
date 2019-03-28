#pragma GCC optimize(3)
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, M;

const int MAXN = 1e5 + 5;

inline void scan_int(int *p) {
    static char c;
    while ((c = getchar_unlocked()) < '0')
        ; // just to be safe
    for (*p = c - '0'; (c = getchar_unlocked()) >= '0'; *p = *p * 10 + c - '0')
        ;
}

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
        fill(begin(level), end(level), -1);
        level[s] = 0;
        while (!q.empty() && level[t] == -1) {
            int v = q.front();
            q.pop();
            for (auto &e : adj[v]) {
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

    T calc() {
        T flow = 0;
        for (lim = SCALING ? (1 << 30) : 1; lim > 0; lim >>= 1) {
            while (bfs()) {
                fill(begin(ptr), end(ptr), 0);
                while (T pushed = dfs(s, INF))
                    flow += pushed;
            }
        }
        return flow;
    }
};

Dinic<MAXN, long long> dinic;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // cin >> N >> M;
    int P;
    scan_int(&N);
    scan_int(&M);
    scan_int(&P);
    // int S = 1, T = N;
    // scan_int(&S);
    // scan_int(&T);
    for (int i = 0; i < N; i++)
        dinic.addEdge(dinic.s, i, 1);
    for (int i = 0; i < M; i++)
        dinic.addEdge(N + i, dinic.t, 1);
    for (ll i = 0; i < P; i++) {
        int a, b;
        scan_int(&a), scan_int(&b);
        // cin >> a >> b >> d;
        a--, b--;
        dinic.addEdge(a, b + N, 1);
    }
    cout << dinic.calc() << endl;
}