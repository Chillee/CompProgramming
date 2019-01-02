#include <bits/stdc++.h>

using namespace std;

const int MAXN = 70;
struct Dinic {
    const static int MAXV = MAXN * 2;
    const int INF = 1e9 + 5;
    struct edge {
        int to, rev, cap, flow;
    };
    const static int s = MAXV - 2;
    const static int t = MAXV - 1;

    int d[MAXV], ptr[MAXV];
    vector<edge> adj[MAXV];

    void addEdge(int a, int b, int cap, int rcap = -1) {
        adj[a].push_back({b, adj[b].size(), cap, 0});
        if (rcap == -1)
            rcap = cap;
        adj[b].push_back({a, adj[a].size() - 1, rcap, 0});
    }

    bool bfs() {
        queue<int> q({s});
        fill(begin(d), end(d), -1);
        d[s] = 0;
        while (!q.empty() && d[t] == -1) {
            int v = q.front();
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

    int dfs(int v, int flow) {
        if (v == t || !flow)
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
            while (int pushed = dfs(s, INF))
                flow += pushed;
        }
        return flow;
    }
};

int K;
bool grid[8][8];
string convert(array<int, 2> cur) {
    char c = cur[1] + 'a';
    char r = cur[0] + '0' + 1;
    string res;
    res += c;
    res += r;
    return res;
}
Dinic dinic;
vector<array<int, 2>> moves = {{2, 1}, {2, -1}, {1, 2}, {1, -2}, {-2, 1}, {-2, -1}, {-1, 2}, {-1, -2}};
bool isValid(int r, int c) { return r >= 0 && c >= 0 && r < 8 && c < 8; }
vector<string> ans;
void dfs() {
    queue<int> q;
    q.push(dinic.MAXV - 2);
    while (q.size() > 0) {
        int cur = q.front();
        q.pop();
        // cout << cur << endl;
        if (cur == dinic.t) {
            return;
        }
        for (auto &i : dinic.adj[cur]) {
            // cout << i.flow << " " << i.to << endl;
            // cout << convert({(i.to - MAXN) / 8, (i.to - MAXN) % 8)}) << endl;
            if (i.flow > 0) {
                i.flow = 0;
                if (cur != dinic.s && i.to != dinic.t && cur % MAXN != i.to % MAXN) {
                    // ans.push_back(convert({i.to / 8, i.to % 8}) + "-" + convert({cur / 8, cur % 8}));
                    ans.push_back(convert({(cur % MAXN) / 8, (cur % MAXN) % 8}) + "-" + convert({(i.to % MAXN) / 8, (i.to % MAXN) % 8}));
                }
                q.push(i.to);
            }
        }
    }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> K;
    for (int i = 0; i < K; i++) {
        char a;
        int r, c;
        cin >> a >> r;
        c = a - 'a';
        r--;
        dinic.addEdge(dinic.s, r * 8 + c + MAXN, 1);
        // dinic.addEdge(r * 8 + c + MAXN, r * 8 + c, 1);
        // grid[r][c] = true;
    }
    for (int i = 0; i < 64; i++) {
        dinic.addEdge(i + MAXN, i, 1);
    }
    for (int i = 0; i < K; i++) {
        dinic.addEdge(i, dinic.t, 1);
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            for (auto m : moves) {
                int nx = i + m[0], ny = j + m[1];
                if (isValid(nx, ny)) {
                    dinic.addEdge(i * 8 + j, nx * 8 + ny + MAXN, 1);
                    // dinic.addEdge(nx * 8 + ny + MAXN, nx * 8 + ny, 1);
                }
            }
        }
    }

    int res = dinic.calc();
    dfs();
    cout << ans.size() << endl;
    // reverse(ans.begin(), ans.end());
    for (auto i : ans) {
        cout << i << endl;
    }
}