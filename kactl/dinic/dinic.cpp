#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct Dinic {
	struct Edge {
		int to, rev;
		ll c, f;
	};
	vi lvl, ptr, q;
	vector<vector<Edge>> adj;
	Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
	void addEdge(int a, int b, ll c, int rcap = 0) {
		adj[a].push_back({b, sz(adj[b]), c, 0});
		adj[b].push_back({a, sz(adj[a]) - 1, rcap, 0});
	}
	ll dfs(int v, int t, ll f) {
		if (v == t || !f) return f;
		for (int& i = ptr[v]; i < sz(adj[v]); i++) {
			Edge& e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (ll p = dfs(e.to, t, min(f, e.c - e.f))) {
					e.f += p, adj[e.to][e.rev].f -= p;
					return p;
				}
		}
		return 0;
	}
	ll calc(int s, int t) {
		ll flow = 0; q[0] = s;
		rep(L,30,31) do {
			lvl = ptr = vi(sz(q));
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int v = q[qi++];
				trav(e, adj[v])
					if (!lvl[e.to] && (e.c-e.f) >> (30-L))
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
		} while (lvl[t]);
		return flow;
	}
};




const int MAXN = 1e5 + 5;
void SPOJMATCHING() {
    int N, M, P;
    cin >> N >> M >> P;
    Dinic flow(N + M + 2);
    for (int i = 0; i < N; i++)
        flow.addEdge(0, 2 + i, 1);
    for (int i = 0; i < M; i++)
        flow.addEdge(2 + N + i, 1, 1);
    for (ll i = 0; i < P; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        flow.addEdge(2 + a, 2 + b + N, 1);
    }
    cout << flow.calc(0, 1) << endl;
}
void LOJ() {
    int N, M, S, T;
    cin >> N >> M >> S >> T;
    S--, T--;
    Dinic flow(N);
    for (int i = 0; i < M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        flow.addEdge(a, b, c);
    }
    cout << flow.calc(S, T) << endl;
}
void FASTFLOW() {
    int N, M;
    cin >> N >> M;
    Dinic flow(N);
    for (int i = 0; i < M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        flow.addEdge(a, b, c, c);
    }
    cout << flow.calc(0, N - 1) << endl;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // FASTFLOW();
    SPOJMATCHING();
    // LOJ();
}