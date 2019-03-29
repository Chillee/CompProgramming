template <int MAXN> struct Dsu {
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