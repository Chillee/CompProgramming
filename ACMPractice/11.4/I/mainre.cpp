#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
const int MAXH = 25;
int N, R;
vector<array<int, 3>> edges;

struct Dsu {
    int par[MAXN], sz[MAXN];
    Dsu(int n) { iota(par, par + n, 0), fill(sz, sz + n, 1); }
    int root(int v) { return v == par[v] ? v : (par[v] = root(par[v])); }

    void merge(int a, int b) {
        if ((a = root(a)) == (b = root(b)))
            return;
        if (sz[a] < sz[b])
            swap(a, b);
        par[b] = a;
        sz[a] += sz[b];
    }
};
int tin[MAXN], tout[MAXN];
int par[MAXN][MAXH];
int mx[MAXN][MAXH];
vector<array<int, 2>> adj[MAXN];

int timer = 0;
void root(int cur, int prv, int prvD) {
    tin[cur] = ++timer;
    par[cur][0] = prv;
    mx[cur][0] = prvD;
    for (int l = 1; l < MAXH; l++) {
        par[cur][l] = par[par[cur][l - 1]][l - 1];
        mx[cur][l] = max(mx[cur][l - 1], mx[par[cur][l - 1]][l - 1]);
    }
    for (auto i : adj[cur]) {
        if (i[1] == prv)
            continue;
        root(i[1], cur, i[0]);
    }
    tout[cur] = ++timer;
}
bool isAncestor(int p, int x) { return tin[x] >= tin[p] && tout[x] <= tout[p]; }
int getMx(int p, int x) {
    assert(isAncestor(p, x));
    // cout << "px: " << p << " " << x << endl;
    int res = 0;
    for (int l = MAXH - 1; l >= 0; l--) {
        if (!isAncestor(par[x][l], p)) {
            // cout << "par: " << par[x][l] << endl;
            // cout << "x,l: " << x << ' ' << l << ' ' << mx[x][l] << endl;
            res = max(res, mx[x][l]);
            x = par[x][l];
        }
    }
    return max(res, mx[x][0]);
}

int lca(int a, int b) {
    if (isAncestor(a, b))
        return getMx(a, b);
    if (isAncestor(b, a))
        return getMx(b, a);
    int cur = a;
    for (int l = MAXH - 1; l >= 0; l--) {
        if (!isAncestor(par[cur][l], b)) {
            cur = par[cur][l];
        }
    }
    cur = par[cur][0];
    // cout << "par: " << cur << endl;
    // cout << getMx(cur, b) << ' ' << getMx(cur, a) << endl;
    return max(getMx(cur, b), getMx(cur, a));
}

map<array<int, 2>, int> ecost;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> R;
    for (int i = 0; i < R; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        edges.push_back({c, a, b});
        ecost[{a, b}] = c;
        ecost[{b, a}] = c;
    }
    sort(edges.begin(), edges.end());
    Dsu kruskal(N);
    vector<array<int, 3>> mst;
    int cost = 0;
    for (auto i : edges) {
        if (kruskal.root(i[1]) != kruskal.root(i[2])) {
            kruskal.merge(i[1], i[2]);
            mst.push_back(i);
            cost += i[0];
        }
    }
    for (auto i : mst) {
        adj[i[1]].push_back({i[0], i[2]});
        adj[i[2]].push_back({i[0], i[1]});
    }
    root(0, 0, 0);
    int Q;
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        cout << cost + ecost[{a, b}] - lca(a, b) << endl;
    }
}