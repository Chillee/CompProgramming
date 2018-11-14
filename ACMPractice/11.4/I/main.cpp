#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
const int MAXB = 25;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

const int RANDOM = (long long)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
unsigned hash_f(unsigned x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}
unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }
struct chash {
    int operator()(array<int, 2> x) const { return hash_combine(hash_f(x[0]), hash_f(x[1])); }
};
struct Dsu {
    int par[MAXN], sz[MAXN];
    void init(int n) { iota(par, par + n, 0), fill(sz, sz + n, 1); }
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
int N, R;
vector<array<int, 3>> edges;
int tin[MAXN], tout[MAXN];
int pars[MAXN][MAXB + 2];
int mx[MAXN][MAXB + 2];
vector<array<int, 2>> adj[MAXN];
int timer;
void rootT(int cur, int p, int pd, int d) {
    tin[cur] = ++timer;
    pars[cur][0] = p;
    mx[cur][0] = pd;
    for (int l = 1; l < MAXB; l++) {
        pars[cur][l] = pars[pars[cur][l - 1]][l - 1];
        mx[cur][l] = max(mx[cur][l - 1], mx[pars[cur][l - 1]][l - 1]);
    }
    for (auto i : adj[cur]) {
        if (i[1] == p)
            continue;
        rootT(i[1], cur, i[0], d + 1);
    }
    tout[cur] = ++timer;
}
bool isAncestor(int u, int v) { return tin[u] <= tin[v] && tout[u] >= tout[v]; }
int getMx(int u, int v) {
    assert(isAncestor(u, v));
    int res = 0;
    for (int l = MAXB - 1; l >= 0; l--) {
        if (isAncestor(u, pars[v][l])) {
            res = max(res, mx[v][l]);
            v = pars[v][l];
        }
    }
    return res;
}
int lca(int a, int b) {
    int origA = a, origB = b;
    int res = 0;
    if (isAncestor(a, b)) {
        return getMx(a, b);
    } else if (isAncestor(b, a)) {
        return getMx(b, a);
    }
    for (int l = MAXB - 1; l >= 0; l--) {
        if (!isAncestor(pars[a][l], b)) {
            a = pars[a][l];
        }
    }
    a = pars[a][0];
    return max(getMx(a, origA), getMx(a, origB));
}

gp_hash_table<array<int, 2>, int, chash> emap;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> R;
    for (int i = 0; i < R; i++) {
        int a, b, d;
        cin >> a >> b >> d;
        edges.push_back({d, a, b});
        emap[{a, b}] = d;
        emap[{b, a}] = d;
    }
    sort(edges.begin(), edges.end());
    Dsu dsu;
    dsu.init(N + 1);
    vector<array<int, 3>> mst;
    int mstD = 0;
    for (auto i : edges) {
        if (dsu.root(i[1]) != dsu.root(i[2])) {
            mstD += i[0];
            mst.push_back(i);
            dsu.merge(i[1], i[2]);
        }
    }
    for (auto i : mst) {
        adj[i[1]].push_back({i[0], i[2]});
        adj[i[2]].push_back({i[0], i[1]});
    }
    rootT(1, 1, 0, 0);
    int Q;
    cin >> Q;
    for (int t = 0; t < Q; t++) {
        int a, b;
        cin >> a >> b;
        cout << mstD - lca(a, b) + emap[{a, b}] << endl;
    }
}