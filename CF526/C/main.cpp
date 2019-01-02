#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
const int MAXN = 2e5 + 5;
vector<int> adj[MAXN];
struct LCA {
    const static int MAXN = ::MAXN;
    const static int MAXB = 24;
    int tim[MAXN], depth[MAXN];
    array<int, 2> st[MAXN * 2][MAXB];
    vector<array<int, 2>> euler;
    void calc(int cur = 0, int p = 0, int d = 0) {
        depth[cur] = d;
        tim[cur] = euler.size();
        euler.push_back({d, cur});
        for (auto i : adj[cur]) {
            if (i == p)
                continue;
            calc(i, cur, d + 1);
            euler.push_back({d, cur});
        }
        if (p == cur) {
            for (int i = 0; i < euler.size(); i++)
                st[i][0] = euler[i];
            for (int j = 1; j <= MAXB; j++)
                for (int i = 0; i + (1 << j) <= euler.size(); i++)
                    st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
    int query(int a, int b) {
        if (a == b)
            return a;
        if ((a = tim[a]) > (b = tim[b]))
            swap(a, b);
        int k = 31 - __builtin_clz(b - a);
        return min(st[a][k], st[b - (1 << k)][k])[1];
    }
    int dist(int a, int b) {
        int lca = query(a, b);
        return depth[a] + depth[b] - 2 * depth[lca];
    }
};

LCA lca;
int N;
int par[MAXN];
int P[MAXN];
int rP[MAXN];
pair<bool, array<int, 2>> canMerge(array<int, 4> pts) {
    auto cmp = [&](int a, int b) { return make_pair(lca.depth[a], a) > make_pair(lca.depth[b], b); };
    sort(pts.begin(), pts.end(), cmp);
    do {
        if (lca.dist(pts[0], pts[1]) + lca.dist(pts[1], pts[2]) + lca.dist(pts[2], pts[3]) == lca.dist(pts[0], pts[3]))
            return {true, {pts[0], pts[3]}};
    } while (next_permutation(pts.begin() + 1, pts.end(), cmp));
    return {false, {0, 0}};
}

struct Tree {
    Tree *pl, *pr;
    int nl = 0, nr = 0;
    int a = -1, b = -1;
    bool val;

    void updateVal() {
        if (!pl->val || !pr->val) {
            val = false;
            a = -1, b = -1;
        } else {
            auto res = canMerge({pl->a, pl->b, pr->a, pr->b});
            if (res.first) {
                a = res.second[0];
                b = res.second[1];
                val = true;
            } else {
                val = false;
                a = -1, b = -1;
            }
        }
    }
    Tree(int l, int r) {
        nl = l, nr = r;
        if (nl + 1 == nr) {
            a = rP[l], b = rP[l];
            val = true;
            return;
        }
        pl = new Tree(nl, nl + nr >> 1);
        pr = new Tree(nl + nr >> 1, nr);
        updateVal();
    }
    void modify(int p) {
        if (p < nl || nr <= p) {
            return;
        }
        if (nl + 1 == nr) {
            a = rP[nl], b = rP[nl];
            val = true;
            return;
        }
        pl->modify(p);
        pr->modify(p);
        updateVal();
    }
    pair<int, array<int, 2>> query(int ca, int cb) {
        if (val) {
            auto res = canMerge({ca, cb, a, b});
            if (res.first)
                return {nr, res.second};
        }
        if (nl + 1 == nr) {
            return {-1, {}};
        }
        auto res = pl->query(ca, cb);
        if (res.first != pl->nr)
            return res;
        else {
            ca = res.second[0], cb = res.second[1];
            res = max(res, pr->query(ca, cb));
            return res;
        }
    }
};
Tree *seg;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> P[i];
        rP[P[i]] = i;
    }
    for (int i = 1; i < N; i++) {
        cin >> par[i];
        par[i]--;
        adj[par[i]].push_back(i);
    }
    lca.calc();
    seg = new Tree(0, N);
    int Q;
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int a, b;
            cin >> a >> b;
            a--, b--;
            swap(P[a], P[b]);
            rP[P[a]] = a;
            rP[P[b]] = b;
            seg->modify(P[a]);
            seg->modify(P[b]);
        } else {
            cout << seg->query(rP[0], rP[0]).first << endl;
        }
    }
}