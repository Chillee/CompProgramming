// Highest label push-relablel
// Testing for https://codeforces.com/blog/entry/66006
// ~dacin21

#pragma GCC optimize("O3")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native") // codeforces

#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 1200 + 10;
constexpr int MAXM = 120000 + 10;

// You need int64_t in theory, but this seems to suffice.
using cap_t = int32_t;
using ex_t = int32_t;

struct Edge {
    int to, rev;
    cap_t f;
};

tuple<int, int, cap_t, cap_t> edge_pool[MAXM];
int g_pos[MAXN];
Edge g[2 * MAXM];
ex_t excess[MAXN];
vector<int> buck[2 * MAXN];
int q[MAXN];

int cur[MAXN], h[MAXN], h_cnt[2 * MAXN];

template <bool global_relabeling = true, bool min_cut_only = true, bool shuffle_edges = false> class Push_Relabel {
  public:
    Push_Relabel(int n_) : n(n_), m(0) {}
    void add_edge(int u, int v, cap_t c, cap_t c_rev = 0) {
        edge_pool[m] = make_tuple(u, v, c, c_rev);
        ++m;
    }
    ex_t max_flow(int s_, int t_) {
        s = s_;
        t = t_;
        run_pr();
        return excess[t] - 1;
    }
    void compile_g() {
        if (shuffle_edges)
            random_shuffle(edge_pool, edge_pool + m);
        for (int it = 0; it < m; ++it) {
            auto &e = edge_pool[it];
            ++g_pos[get<0>(e)];
            ++g_pos[get<1>(e)];
        }
        for (int i = 0; i < n; ++i) {
            g_pos[i + 1] += g_pos[i];
        }
        for (int it = 0; it < m; ++it) {
            auto &e = edge_pool[it];
            int u, v;
            cap_t c, c_rev;
            tie(u, v, c, c_rev) = e;
            const int i = --g_pos[u], j = --g_pos[v];
            g[i] = Edge{v, j, c};
            g[j] = Edge{u, i, c_rev};
        }
    }
    void global_relabel(int &hi) {
        fill(h, h + n, n);
        fill(h_cnt, h_cnt + 2 * n, 0);
        q[0] = t;
        h[t] = 0;
        buck[0].clear();
        for (int it = 0, it_end = 1; it < it_end; ++it) {
            const int u = q[it];
            if (u != t && excess[u]) {
                hi = h[u];
                buck[h[u]].push_back(u);
            }
            ++h_cnt[h[u]];
            for (int i = g_pos[u], i_end = g_pos[u + 1]; i < i_end; ++i) {
                Edge const &e = g[i];
                if (g[e.rev].f && h[e.to] == n) {
                    h[e.to] = h[u] + 1;
                    q[it_end++] = e.to;
                }
            }
        }
        assert(h[s] == n);
    }
    void push(int u, Edge &e, ex_t f) {
        if (!excess[e.to]) {
            buck[h[e.to]].push_back(e.to);
        }
        Edge &back = g[e.rev];
        e.f -= f;
        back.f += f;
        excess[e.to] += f;
        excess[u] -= f;
    }

    void init_pr() {
        compile_g();
        copy(g_pos, g_pos + n, cur);
        h[s] = n;
        h_cnt[n] = 1;
        h_cnt[0] = n - 1;
        excess[t] = 1;
    }
    void run_pr() {
        init_pr();
        for (int i = g_pos[s], i_end = g_pos[s + 1]; i < i_end; ++i) {
            push(s, g[i], g[i].f);
        }
        int hi = 0;
        if (global_relabeling)
            global_relabel(hi);
        if (!buck[hi].empty())
            for (; hi >= 0;) {
                int u = buck[hi].back();
                buck[hi].pop_back();
                int u_cur = cur[u];
                // discharge
                if (!min_cut_only || h[u] < n)
                    while (excess[u] > 0) {
                        if (u_cur == g_pos[u + 1]) {
                            h[u] = 1e9;
                            for (int i = g_pos[u], i_end = g_pos[u + 1]; i < i_end; ++i) {
                                auto const &e = g[i];
                                if (e.f && h[u] > h[e.to] + 1) {
                                    h[u] = h[e.to] + 1;
                                    u_cur = i;
                                }
                            }
                            ++h_cnt[h[u]];
                            if (!--h_cnt[hi] && hi < n) {
                                for (int i = 0; i < n; ++i) {
                                    if (hi <= h[i] && h[i] < n) {
                                        --h_cnt[h[i]];
                                        h[i] = n + 1;
                                    }
                                }
                            }
                            hi = h[u];
                        } else {
                            Edge &e_cur = g[u_cur];
                            if (e_cur.f && h[u] == h[e_cur.to] + 1) {
                                push(u, e_cur, min(excess[u], e_cur.f));
                            } else
                                ++u_cur;
                        }
                    }
                cur[u] = u_cur;
                while (hi >= 0 && buck[hi].empty())
                    --hi;
            }
    }
    int n, m, s, t;
};

char buf[32 * 1024];
int curPos, endPos;
inline char gc() {
    if (curPos == endPos) {
        endPos = fread(buf, 1, sizeof(buf), stdin);
        curPos = 0;
    }
    return buf[curPos++];
}
inline void readint(int &x) {
    char c = gc();
    x = 0;
    while (c < '0' || c > '9')
        c = gc();
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = gc();
    }
}
int main() {
#ifdef LOCAL_RUN
    freopen("in.txt", "r", stdin);
#endif
    int N, M, s, t;
    cin >> N >> M >> s >> t;
    // readint(N);
    // readint(M);
    // readint(s);
    // readint(t);
    Push_Relabel<> fl(N + 1);
    int u, v, w;
    for (int i = 1; i <= M; ++i) {
        cin >> u >> v >> w;
        // readint(u);
        // readint(v);
        // readint(w);
        fl.add_edge(u, v, w, 0);
    }
    cout << fl.max_flow(s, t) << endl;
    // printf("%lld\n", fl.max_flow(s, t));

    return 0;
}