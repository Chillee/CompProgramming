#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef ll Flow;
struct Edge {
    int dest, back;
    Flow f, c;
};

struct PushRelabel {
    vector<vector<Edge>> g;
    vector<Flow> excess;
    vector<Edge *> cur;
    vector<vector<int>> lst;
    vector<int> height;
    PushRelabel(int n) : g(n), excess(n), cur(n), lst(2 * n), height(n) {}
    void add_edge(int s, int t, Flow cap, Flow rcap = 0) {
        if (s == t)
            return;
        Edge a = {t, (g[t]).size(), 0, cap};
        Edge b = {s, (g[s]).size(), 0, rcap};
        g[s].push_back(a);
        g[t].push_back(b);
    }
    void add_flow(Edge &e, Flow f) {
        Edge &back = g[e.dest][e.back];
        if (!excess[e.dest] && f)
            lst[height[e.dest]].push_back(e.dest);
        e.f += f;
        e.c -= f;
        excess[e.dest] += f;
        back.f -= f;
        back.c += f;
        excess[back.dest] -= f;
    }
    Flow maxflow(int s, int t) {
        int v = (g).size();
        height[s] = v;
        excess[t] = 1;
        vector<int> cnt(2 * v);
        cnt[0] = v - 1;
        for (int i = 0; i < v; i++)
            cur[i] = g[i].data();
        for (auto e : g[s])
            add_flow(e, e.c);
        for (int hi = 0;;) {
            while (lst[hi].empty())
                if (!hi--)
                    return -excess[s];
            int u = lst[hi].back();
            lst[hi].pop_back();
            while (excess[u] > 0) // discharge u
                if (cur[u] == g[u].data() + (g[u]).size()) {
                    height[u] = 1e9;
                    for (auto &e : g[u])
                        if (e.c && height[u] > height[e.dest] + 1)
                            height[u] = height[e.dest] + 1, cur[u] = &e;
                    if (++cnt[height[u]], !--cnt[hi] && hi < v)
                        for (int i = 0; i < v; i++)
                            if (hi < height[i] && height[i] < v)
                                --cnt[height[i]], height[i] = v + 1;
                    hi = height[u];
                } else if (cur[u]->c && height[u] == height[cur[u]->dest] + 1)
                    add_flow(*cur[u], min(excess[u], cur[u]->c));
                else
                    ++cur[u];
        }
    }
};
PushRelabel *hlpp;
inline void scan_int(int *p) {
    static char c;
    while ((c = getchar_unlocked()) < '0')
        ; // just to be safe
    for (*p = c - '0'; (c = getchar_unlocked()) >= '0'; *p = *p * 10 + c - '0')
        ;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m, p;
    scan_int(&n), scan_int(&m);
    hlpp = new PushRelabel(n + 1);
    int s = 1, t = n;
    scan_int(&s), scan_int(&t);
    for (int i = 0, u, v, f; i < m; ++i) {
        scan_int(&u), scan_int(&v), scan_int(&f);
        hlpp->add_edge(u, v, f, 0);
    }
    int ans = hlpp->maxflow(s, t);
    cout << ans << endl;
    return 0;
}