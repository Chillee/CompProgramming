#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

const int RANDOM = (uint64_t)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
unsigned hash_f(unsigned x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}
unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }
struct chash {
    int operator()(int x) const { return hash_f(x); }
};
int T, N;
int V[MAXN];
int stSize[MAXN];
vector<int> child[MAXN];
vector<int> adj[MAXN];
int ans[MAXN];

bool vis[MAXN];
int root(int cur) {
    if (vis[cur])
        return 0;
    vis[cur] = true;
    int sz = 1;
    for (auto i : adj[cur]) {
        if (vis[i])
            continue;
        child[cur].push_back(i);
        sz += root(i);
    }
    stSize[cur] = sz;
    return sz;
}
struct seg {
    int n = 4e5 + 5;
    const int OFFSET = 2e5;
    int curMax = 0;
    gp_hash_table<int, int, chash> seg;
    bool valid = true;

    int get(int x) { return (seg.find(x) == seg.end()) ? 0 : seg[x]; }
    void modify(int p, int val) {
        seg[p += OFFSET]++;
        if (seg[p] > curMax) {
            curMax = seg[p];
        }
        return;
    }

    int query() { return curMax; }
    void clear() { seg.clear(); }
};
void genTree(int cur, int depth, vector<int> &res, int dir) {
    res.push_back(V[cur] + dir * depth);
    for (auto i : child[cur])
        genTree(i, depth + 1, res, dir);
}

void calc(int cur, int depth, array<seg, 2> &res) {
    if (child[cur].size() == 0) {
        res[0].clear();
        res[0].modify(V[cur] + depth, 1);
        res[1].clear();
        res[1].modify(V[cur] - depth, 1);
        ans[cur] = 0;
        return;
    } else if (child[cur].size() > 2) {
        for (auto i : child[cur]) {
            array<seg, 2> t;
            calc(i, depth + 1, t);
        }
        ans[cur] = -1;
        res[0].valid = false;
        return;
    } else if (child[cur].size() == 1) {
        calc(child[cur][0], depth + 1, res);
        if (!res[0].valid) {
            ans[cur] = -1;
            return;
        }
        res[0].modify(V[cur] + depth, 1);
        res[1].modify(V[cur] - depth, 1);
        int mxCount = max(res[0].query(), res[1].query());
        ans[cur] = stSize[cur] - mxCount;
        return;
    } else if (child[cur].size() == 2) {
        array<seg, 2> resl, resr;
        calc(child[cur][0], depth + 1, resl);
        calc(child[cur][1], depth + 1, resr);
        if (!resl[0].valid || !resr[0].valid) {
            ans[cur] = -1;
            res[0].valid = false;
            return;
        }
        vector<int> plnr = {V[cur]};
        genTree(child[cur][0], 1, plnr, 1);
        genTree(child[cur][1], 1, plnr, -1);
        int cans = 0;
        gp_hash_table<int, int, chash> counts;
        for (auto i : plnr) {
            counts[i]++;
        }
        for (auto i : counts) {
            cans = max(i.second, cans);
        }
        vector<int> nlpr = {V[cur]};
        genTree(child[cur][0], 1, nlpr, -1);
        genTree(child[cur][1], 1, nlpr, 1);
        counts.clear();
        for (auto i : nlpr) {
            counts[i]++;
        }
        for (auto i : counts) {
            cans = max(i.second, cans);
        }
        ans[cur] = stSize[cur] - cans;

        res[0].valid = false;
        return;
    }
    assert(false);
    return;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int t = 0; t < T; t++) {
        for (int i = 0; i < MAXN; i++) {
            child[i].clear();
            adj[i].clear();
        }
        fill(begin(ans), end(ans), -1);
        fill(begin(vis), end(vis), 0);
        fill(begin(stSize), end(stSize), 0);
        fill(begin(V), end(V), 0);
        cin >> N;
        for (int i = 0; i < N; i++)
            cin >> V[i];
        for (int i = 0; i < N - 1; i++) {
            int a, b;
            cin >> a >> b;
            a--, b--;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        root(0);
        array<seg, 2> res;
        calc(0, 0, res);
        for (int i = 0; i < N; i++) {
            cout << ans[i] << ' ';
        }
        cout << endl;
    }
}