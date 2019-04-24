#pragma GCC optimize(3)
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5005;

template <int MAXN, class T = int> struct HLPP {
    const T INF = numeric_limits<T>::max();
    struct edge {
        int to, rev;
        T f;
    };
    int s = MAXN - 1, t = MAXN - 2;
    vector<edge> adj[MAXN];
    vector<int> lst[MAXN], gap[MAXN];
    T excess[MAXN];
    int highest, height[MAXN], cnt[MAXN], work;
    void addEdge(int from, int to, T f, bool isDirected = true) {
        adj[from].push_back({to, adj[to].size(), f});
        adj[to].push_back({from, adj[from].size() - 1, isDirected ? 0 : f});
    }
    void updHeight(int v, int nh) {
        work++;
        if (height[v] != MAXN)
            cnt[height[v]]--;
        height[v] = nh;
        if (nh == MAXN)
            return;
        cnt[nh]++, highest = nh;
        gap[nh].push_back(v);
        if (excess[v] > 0)
            lst[nh].push_back(v);
    }
    void globalRelabel() {
        work = 0;
        fill(height, height + MAXN, MAXN);
        fill(cnt, cnt + MAXN, 0);
        for (int i = 0; i < highest; i++)
            lst[i].clear(), gap[i].clear();
        height[t] = 0;
        queue<int> q({t});
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto &e : adj[v])
                if (height[e.to] == MAXN && adj[e.to][e.rev].f > 0)
                    q.push(e.to), updHeight(e.to, height[v] + 1);
            highest = height[v];
        }
    }
    void push(int v, edge &e) {
        if (excess[e.to] == 0)
            lst[height[e.to]].push_back(e.to);
        T df = min(excess[v], e.f);
        e.f -= df, adj[e.to][e.rev].f += df;
        excess[v] -= df, excess[e.to] += df;
    }
    void discharge(int v) {
        int nh = MAXN;
        for (auto &e : adj[v]) {
            if (e.f > 0) {
                if (height[v] == height[e.to] + 1) {
                    push(v, e);
                    if (excess[v] <= 0)
                        return;
                } else
                    nh = min(nh, height[e.to] + 1);
            }
        }
        if (cnt[height[v]] > 1)
            updHeight(v, nh);
        else {
            for (int i = height[v]; i <= highest; i++) {
                for (auto j : gap[i])
                    updHeight(j, MAXN);
                gap[i].clear();
            }
        }
    }
    T calc(int heur_n = MAXN) {
        fill(begin(excess), end(excess), 0);
        excess[s] = INF, excess[t] = -INF;
        globalRelabel();
        for (auto &e : adj[s])
            push(s, e);
        for (; highest >= 0; highest--) {
            while (!lst[highest].empty()) {
                int v = lst[highest].back();
                lst[highest].pop_back();
                discharge(v);
                if (work > 4 * heur_n)
                    globalRelabel();
            }
        }
        return excess[t] + INF;
    }
};
void read_uint() {}
template <class T, class... S> inline void read_uint(T &a, S &... b) {
    static char c;
    while (isspace(c = getchar_unlocked()))
        ;
    for (a = c - '0'; isdigit(c = getchar_unlocked()); a = a * 10 + c - '0')
        ;
    read_uint(b...);
}
HLPP<MAXN> hlpp;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m, p;
    read_uint(n, m);
    int s = 1, t = n;
    read_uint(s), read_uint(t);
    for (int i = 0, u, v, f; i < m; ++i) {
        read_uint(u), read_uint(v), read_uint(f);
        hlpp.addEdge(u, v, f, true);
    }
    hlpp.s = s, hlpp.t = t;
    int ans = hlpp.calc(n);
    cout << ans << endl;
    return 0;
    // vector<array<int, 3>> res;
    // for (int i = 0; i < MAXN; i++) {
    //     for (auto j : hlpp.adj[i]) {
    //         if (j.f < j.orig)
    //             res.push_back({i, j.to, j.orig - j.f});
    //     }
    //     // if (hlpp.adj[i].size())
    //     //     cout << endl;
    // }
    // cout << n << ' ' << ans << ' ' << res.size() << endl;
    // for (auto i : res) {
    //     cout << i[0] << ' ' << i[1] << ' ' << i[2] << endl;
    // }
}