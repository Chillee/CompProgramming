#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 2e5 + 5;
const ll INF = 1e9 + 5;
ll MOD;
ll pow10[MAXN];
string s;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> s;
    reverse(s.begin(), s.end());
    cin >> MOD;
    pow10[0] = 1;
    for (ll i = 1; i < MAXN; i++) {
        pow10[i] = (pow10[i - 1] * 10) % MOD;
    }
    ll cur = 0;
    for (ll i = 0; i < s.size(); i++) {
        cur = (cur + (s[i] - '0') * pow10[i]) % MOD;
    }
    ll ans = cur;
    for (ll i = s.size() - 1; i > 0; i--) {
        cur -= pow10[s.size() - 1] * (s[i] - '0');
        cur = ((cur % MOD) + MOD) % MOD;
        cur *= 10;
        cur += s[i] - '0';
        cur %= MOD;
        if (s[i - 1] != '0') {
            ans = min(ans, cur);
        }
    }
    cout << ans << endl;
}
struct Dinic {
    const static int MAXV = MAXN;
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