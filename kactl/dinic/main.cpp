#include <bits/stdc++.h>

using namespace std;
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

template <typename cap_t, typename excess_t, bool global_relabeling = true, bool min_cut_only = true>
class PushRelabel {
  public:
    struct Edge {
        int to, rev;
        cap_t f;
    };
    int v, m, s, t, hi;
    vector<tuple<int, int, cap_t, cap_t>> edge_pool;
    vector<int> g_pos;
    vector<Edge> g2;
    vector<vector<Edge *>> g;
    vector<int> q, cur, h, cnt;
    vector<excess_t> ec;
    vector<vector<int>> hs, gap;

    PushRelabel(int n_) : v(n_), m(0), ec(v), hs(2 * v), g(v) {}

    void add_edge(int u, int v, cap_t c, cap_t c_rev = 0) {
        edge_pool.emplace_back(u, v, c, c_rev);
        ++m;
    }
    excess_t maxflow(int s_, int t_) {
        s = s_;
        t = t_;
        run_pr();
        return ec[t] - 1;
    }

    void compile_g() {
        g_pos.resize(v + 1);
        for (auto &e : edge_pool) {
            ++g_pos[get<0>(e)];
            ++g_pos[get<1>(e)];
        }
        for (int i = 0; i < v; ++i) {
            g_pos[i + 1] += g_pos[i];
        }
        g2.resize(g_pos.back());
        for (auto &e : edge_pool) {
            int u, v;
            cap_t c, c_rev;
            tie(u, v, c, c_rev) = e;
            const int i = --g_pos[u], j = --g_pos[v];
            g2[i] = Edge{v, j, c};
            g2[j] = Edge{u, i, c_rev};
            g[u].push_back(&g2[i]);
            g[v].push_back(&g2[j]);
        }
        for (int i = 0; i < v; i++)
            reverse(all(g[i]));
    }
    int work = 0;
    void global_relabel() {
        q.reserve(v);
        fill(h.begin(), h.end(), v);
        fill(cnt.begin(), cnt.end(), 0);
        cnt[v] = 1;
        q.push_back(t);
        h[t] = 0;
        for (auto &e : hs)
            e.clear();
        for (auto &e : gap)
            e.clear();
        for (auto it = q.begin(); it < q.end(); ++it) {
            const int u = *it;
            if (u != t && ec[u]) {
                hi = h[u];
                hs[h[u]].push_back(u);
            }
            if (u != t)
                gap[h[u]].push_back(u);
            ++cnt[h[u]];
            for (int i = g_pos[u], i_end = g_pos[u + 1]; i < i_end; ++i) {
                Edge const &e = g2[i];
                if (g2[e.rev].f && h[e.to] == v) {
                    h[e.to] = h[u] + 1;
                    q.push_back(e.to);
                }
            }
        }
        assert(h[s] == v);
        q.clear();
    }
    void push(int u, Edge &e, excess_t f) {
        if (!ec[e.to]) {
            hs[h[e.to]].push_back(e.to);
        }
        Edge &back = g2[e.rev];
        e.f -= f;
        back.f += f;
        ec[e.to] += f;
        ec[u] -= f;
    }
    void init_pr() {
        compile_g();
        cur.assign(v, 0);
        copy(g_pos.begin(), prev(g_pos.end()), cur.begin());
        h.resize(v);
        gap.resize(v + 1);
        cnt.assign(2 * v, 0);
        h[s] = v;
        cnt[v] = 1;
        cnt[0] = v - 1;
        ec[t] = 1;
    }
    void run_pr() {
        init_pr();
        trav(e, g[s]) push(s, *e, e->f);
        hi = 0;
        if (global_relabeling)
            global_relabel();
        if (!hs[hi].empty())
            for (; hi >= 0;) {
                int u = hs[hi].back();
                hs[hi].pop_back();
                int u_cur = cur[u];
                // discharge
                if (!min_cut_only || h[u] < v)
                    while (ec[u] > 0) {
                        if (u_cur == g_pos[u + 1]) {
                            int new_h = 1e9;
                            int i = g_pos[u];
                            trav(e, g[u]) {
                                if (e->f && new_h > h[e->to] + 1) {
                                    new_h = h[e->to] + 1;
                                    u_cur = i;
                                }
                                i++;
                            }
                            ++cnt[new_h];
                            h[u] = new_h;
                            work++;
                            if (!--cnt[hi] && hi < v) {
                                // gap relabel
                                for (int j = hi; j <= v; ++j) {
                                    for (auto &f : gap[j])
                                        if (!min_cut_only || h[f] < v) {
                                            --cnt[h[f]];
                                            work++;
                                            h[f] = v + 1;
                                        }
                                    gap[j].clear();
                                }
                            }
                            hi = h[u];
                        } else {
                            Edge &e_cur = g2[u_cur];
                            if (e_cur.f && h[u] == h[e_cur.to] + 1) {
                                push(u, e_cur, min<excess_t>(ec[u], e_cur.f));
                            } else
                                ++u_cur;
                        }
                    }
                if (h[u] < v) {
                    gap[h[u]].push_back(u);
                }
                cur[u] = u_cur;
                // if (work > 4 * v)
                //     global_relabel();
                while (hi >= 0 && hs[hi].empty())
                    --hi;
            }
    }
};

void SPOJMATCHING() {
    int N, M, P;
    cin >> N >> M >> P;
    PushRelabel<ll, ll> flow(N + M + 5);
    for (int i = 0; i < N; i++)
        flow.add_edge(0, 2 + i, 1);
    for (int i = 0; i < M; i++)
        flow.add_edge(2 + N + i, 1, 1);
    for (ll i = 0; i < P; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        flow.add_edge(2 + a, 2 + b + N, 1);
    }
    cout << flow.maxflow(0, 1) << endl;
}
void LOJ() {
    int N, M, S, T;
    cin >> N >> M >> S >> T;
    S--, T--;
    PushRelabel<ll, ll> flow(N + M + 2);
    for (int i = 0; i < M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        flow.add_edge(a, b, c);
    }
    cout << flow.maxflow(S, T) << endl;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    SPOJMATCHING();
    // LOJ();
}