#include <bits/stdc++.h>

#define endl '\n';
using namespace std;
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int MAXN = 4005;
int N, M, S;
array<ll, 2> beagles[MAXN / 2];
array<ll, 2> water[MAXN / 2];
int C[MAXN / 2];

const int INF = 1e9 + 5;

// template <int MAXN, class T = int> struct HLPP {
//     const T INF = numeric_limits<T>::max();
//     struct edge {
//         int to, rev;
//         T f;
//     };
//     int s = MAXN - 1, t = MAXN - 2;
//     vector<edge> adj[MAXN];
//     vector<int> lst[MAXN], gap[MAXN];
//     T excess[MAXN];
//     int highest, height[MAXN], cnt[MAXN], work;
//     void addEdge(int from, int to, int f, bool isDirected = true) {
//         adj[from].push_back({to, adj[to].size(), f});
//         adj[to].push_back({from, adj[from].size() - 1, isDirected ? 0 : f});
//     }
//     void updHeight(int v, int nh) {
//         work++;
//         if (height[v] != MAXN)
//             cnt[height[v]]--;
//         height[v] = nh;
//         if (nh == MAXN)
//             return;
//         cnt[nh]++, highest = nh;
//         gap[nh].push_back(v);
//         if (excess[v] > 0)
//             lst[nh].push_back(v);
//     }
//     void globalRelabel() {
//         work = 0;
//         fill(begin(height), end(height), MAXN);
//         fill(begin(cnt), end(cnt), 0);
//         for (int i = 0; i < highest; i++)
//             lst[i].clear(), gap[i].clear();
//         height[t] = 0;
//         queue<int> q({t});
//         while (!q.empty()) {
//             int v = q.front();
//             q.pop();
//             for (auto &e : adj[v])
//                 if (height[e.to] == MAXN && adj[e.to][e.rev].f > 0)
//                     q.push(e.to), updHeight(e.to, height[v] + 1);
//             highest = height[v];
//         }
//     }
//     void push(int v, edge &e) {
//         if (excess[e.to] == 0)
//             lst[height[e.to]].push_back(e.to);
//         T df = min(excess[v], e.f);
//         e.f -= df, adj[e.to][e.rev].f += df;
//         excess[v] -= df, excess[e.to] += df;
//     }
//     void discharge(int v) {
//         int nh = MAXN;
//         for (auto &e : adj[v]) {
//             if (e.f > 0) {
//                 if (height[v] == height[e.to] + 1) {
//                     push(v, e);
//                     if (excess[v] <= 0)
//                         return;
//                 } else
//                     nh = min(nh, height[e.to] + 1);
//             }
//         }
//         if (cnt[height[v]] > 1)
//             updHeight(v, nh);
//         else {
//             for (int i = height[v]; i <= highest; i++) {
//                 for (auto j : gap[i])
//                     updHeight(j, MAXN);
//                 gap[i].clear();
//             }
//         }
//     }
//     T calc(int heur_n = MAXN) {
//         fill(begin(excess), end(excess), 0);
//         excess[s] = INF, excess[t] = -INF;
//         globalRelabel();
//         for (auto &e : adj[s])
//             push(s, e);
//         for (; highest >= 0; highest--) {
//             while (!lst[highest].empty()) {
//                 int v = lst[highest].back();
//                 lst[highest].pop_back();
//                 discharge(v);
//                 if (work > 4 * heur_n)
//                     globalRelabel();
//             }
//         }
//         return excess[t] + INF;
//     }
// };
// HLPP<MAXN> hlpp;

typedef int Flow;
struct Edge {
    int dest, back;
    Flow f, c;
};

struct PushRelabel {
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

    void addFlow(Edge &e, Flow f) {
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
        trav(e, g[s]) addFlow(e, e.c);

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
                    addFlow(*cur[u], min(ec[u], cur[u]->c));
                else
                    ++cur[u];
        }
    }
};
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M >> S;
    PushRelabel hlpp(2 + N + M);
    for (int i = 0; i < N; i++) {
        cin >> beagles[i][0] >> beagles[i][1];
    }
    for (int i = 0; i < M; i++) {
        cin >> water[i][0] >> water[i][1] >> C[i];
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            ll dx = beagles[i][0] - water[j][0];
            ll dy = beagles[i][1] - water[j][1];
            if (sqrt(dx * dx + dy * dy) + 10 <= S) {
                hlpp.addEdge(2 + i, 2 + N + j, 1, 0);
            }
        }
    }
    for (int i = 0; i < M; i++) {
        hlpp.addEdge(2 + N + i, 1, C[i], 0);
    }
    for (int i = 0; i < N; i++) {
        hlpp.addEdge(0, 2 + i, 1, 0);
    }
    // cout << dinic() << endl;
    cout << (hlpp.maxflow(0, 1) == N ? "YES" : "NO") << endl;
}