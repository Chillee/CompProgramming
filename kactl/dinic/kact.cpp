#include <bits/stdc++.h>

using namespace std;
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

typedef ll Flow;
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
    PushRelabel(int n) : g(n), ec(n), cur(n), hs(2 * n), H(n, n) {}

    void add_edge(int s, int t, Flow cap, Flow rcap = 0) {
        if (s == t)
            return;
        Edge a = {t, sz(g[t]), 0, cap};
        Edge b = {s, sz(g[s]), 0, rcap};
        g[s].push_back(a);
        g[t].push_back(b);
    }

    void add_flow(Edge &e, Flow f) {
        Edge &back = g[e.dest][e.back];
        cout << "adding(dest, f): " << e.dest << ' ' << f << endl;
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
        // fill(all(H), 0);
        const int INF = 1e9;
        ec[t] = 1;
        ec[s] = INF;
        vi cnt(2 * v);
        // cnt[0] = v - 1;
        int hi = 0;
        H[t] = 0;
        queue<int> q({t});
        while (!q.empty()) {
            int c = q.front();
            q.pop();
            for (auto &e : g[c]) {
                if (H[e.dest] == v && g[e.dest][e.back].c > 0) {
                    q.push(e.dest);
                    H[e.dest] = H[c] + 1;
                }
            }
            hi = max(H[c], hi);
        }
        for (int i = 0; i < v; i++) {
            if (i != t) {
                hs[H[i]].push_back(i);
                cnt[H[i]]++;
            }
        }
        rep(i, 0, v) cout << H[i] << ' ';
        cout << endl;
        rep(i, 0, v) cur[i] = g[i].data();
        trav(e, g[s]) add_flow(e, e.c);
        rep(i, 0, v) cout << ec[i] << ' ';
        cout << endl;
        rep(i, 0, hi + 1) cout << cnt[i] << ' ';
        cout << endl;
        cout << "hi: " << hi << endl;
        int cnter = 0;
        for (;;) {
            // cout<<hi<<' '<<hs[hi].size()<<endl;
            // cout<<"?"<<endl;
            while (hs[hi].empty())
                if (!hi--) {
                    cout << cnter << endl;
                    return -ec[s];
                }
            int u = hs[hi].back();
            hs[hi].pop_back();
            cout << "excess: ";
            rep(i, 0, v) cout << ec[i] << ' ';
            cout << endl;
            cout << "height: ";
            rep(i, 0, v) cout << H[i] << ' ';
            cout << endl;
            cout << "discharging: " << u << endl;
            cout << "lsts: " << endl;
            for (int i = 0; i <= hi; i++) {
                if (!hs[i].empty()) {
                    cout << i << ": ";
                    for (auto j : hs[i])
                        cout << j << ' ';
                    cout << endl;
                }
            }
            cout << endl;
            cout << "source edges" << endl;
            for (auto e : g[0]) {
                cout << e.dest << ' ' << e.c << ' ' << e.f << endl;
            }
            while (ec[u] > 0) { // discharge u
                cnter++;
                if (cur[u] == g[u].data() + sz(g[u])) {
                    H[u] = v;
                    trav(e, g[u]) if (e.c && H[u] > H[e.dest] + 1) {
                        H[u] = H[e.dest] + 1;
                        cur[u] = &e;
                    }
                    cout << hi << ' ' << u << endl;
                    if (++cnt[H[u]], !--cnt[hi] && hi < v)
                        rep(i, 0, v) if (hi < H[i] && H[i] < v)-- cnt[H[i]], H[i] = v + 1;
                    hi = H[u];
                    // cur[u] = g[u].data();
                } else if (cur[u]->c && H[u] == H[cur[u]->dest] + 1) {
                    cout << "adding?? " << H[u] << ' ' << H[cur[u]->dest] << endl;
                    add_flow(*cur[u], min(ec[u], cur[u]->c));
                } else
                    ++cur[u];
            }

            cout << "lsts: " << endl;
            for (int i = 0; i <= hi; i++) {
                if (!hs[i].empty()) {
                    cout << i << ": ";
                    for (auto j : hs[i])
                        cout << j << ' ';
                    cout << endl;
                }
            }
            cout << endl;
        }
    }
};

void SPOJMATCHING() {
    int N, M, P;
    cin >> N >> M >> P;
    PushRelabel flow(N + M + 2);
    // PushRelabel<ll, ll> flow(N + M + 5);
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
    PushRelabel flow(N);
    S--, T--;
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
    // SPOJMATCHING();
    LOJ();
}