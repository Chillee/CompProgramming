#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;

struct MinCostFlow {
    const int INF = 1e9 + 5;
    const int s = 0, t = 1;
    struct edge {
        int from, to, cap, flow, cost;
    };

    int cost[MAXN][MAXN];
    vector<edge> e;
    int dist[MAXN];
    int par[MAXN];

    int minCost(int flow) {
        int result = 0;
        while (true) {
            fill(begin(dist), end(dist), INF);
            dist[s] = 0;
            while (true) {
                bool change = false;
                for (int i = 0; i < e.size(); i++) {
                    int from = e[i].from, to = e[i].to;
                    if (e[i].flow == e[i].cap)
                        continue;
                    if (dist[from] == INF)
                        continue;
                    if (dist[to] > dist[from] + e[i].cost) {
                        dist[to] = dist[from] + e[i].cost;
                        par[to] = i;
                        change = true;
                    }
                }
                if (!change)
                    break;
            }

            if (dist[t] == INF) {
                return -1;
            }

            int push = flow;
            int cur = t;
            while (cur != s) {
                edge tmp = e[par[cur]];
                int from = tmp.from, can_push = tmp.cap - tmp.flow;
                push = min(push, can_push);
                cur = from;
            }

            flow -= push;
            cur = t;
            while (cur != s) {
                edge tmp = e[par[cur]];
                int from = tmp.from;
                e[par[cur]].flow += push;
                e[par[cur] ^ 1].flow -= push;
                result += push * tmp.cost;
                cur = from;
            }

            if (flow == 0)
                break;
        }
        return result;
    }

    void addEdge(int from, int to, int cap, int cost) {
        e.push_back({from, to, cap, 0, cost});
        e.push_back({to, from, cap, cap, -cost});
    }
};
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

int P, R, L;
MinCostFlow dinic;
Dinic dinic2;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> P >> R >> L;
    for (int i = 0; i < L; i++) {
        int a, b;
        cin >> a >> b;
        dinic.addEdge(a + 2, b + 2, 1, 1);
        dinic.addEdge(b + 2, a + 2, 1, 1);
        dinic2.add_edge(a + 2, b + 2, 1, 1);
    }
    int cnt = dinic2.calc();
    int res = dinic.minCost(P);
    if (cnt < P) {
        cout << P - cnt << " people left behind" << endl;
    } else {
        cout << res << endl;
    }
}