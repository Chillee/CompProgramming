#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
const int MAXB = 18;
int depth[MAXN];
int tin[MAXN], tout[MAXN], timer = 0;
int pars[MAXN][MAXB];

vector<int> adj[MAXN];
void root(int cur, int p) {
    tin[cur] = ++timer;
    pars[cur][0] = p;
    depth[cur] = depth[p] + 1;
    for (int d = 1; d < MAXB; d++)
        pars[cur][d] = pars[pars[cur][d - 1]][d - 1];
    for (auto i : adj[cur]) {
        if (i == p)
            continue;
        root(i, cur);
    }
    tout[cur] = ++timer;
}
bool isAncestor(int p, int x) { return tin[p] <= tin[x] && tout[p] >= tout[x]; }
int lca(int a, int b) {
    if (isAncestor(a, b))
        return a;
    if (isAncestor(b, a))
        return b;
    for (int d = MAXB - 1; d >= 0; d--) {
        if (!isAncestor(pars[a][d], b))
            a = pars[a][d];
    }
    return pars[a][0];
}
int dist(int a, int b) {
    int p = lca(a, b);
    return (depth[a] - depth[p]) + (depth[b] - depth[p]);
}
int sz[MAXN];
int cpar[MAXN];
bool dead[MAXN];
int sizedfs(int cur, int p) {
    sz[cur] = 1;
    for (auto i : adj[cur]) {
        if (i != p && !dead[i])
            sz[cur] += sizedfs(i, cur);
    }
    return sz[cur];
}
int getCentroid(int cur, int p, int n) {
    for (auto i : adj[cur]) {
        if (i != p && !dead[i] && sz[i] > n / 2)
            return getCentroid(i, cur, n);
    }
    return cur;
}
void decompose(int cur, int p) {
    sizedfs(cur, cur);
    int centr = getCentroid(cur, cur, sz[cur]);
    cpar[centr] = p;
    dead[centr] = true;
    for (auto i : adj[centr]) {
        if (!dead[i] && i != p)
            decompose(i, centr);
    };
}
int cans[MAXN];
void update(int x) {
    int cur = x;
    while (cur != -1) {
        cans[cur] = min(cans[cur], dist(x, cur));
        cur = cpar[cur];
    }
}
int query(int x) {
    int ans = 1e9 + 5;
    int cur = x;
    while (cur != -1) {
        ans = min(ans, dist(x, cur) + cans[cur]);
        cur = cpar[cur];
    }
    return ans;
}

int N, M;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    root(0, 0);
    decompose(0, -1);
    for (int i = 0; i < N; i++) {
        cans[i] = dist(0, i);
    }
    for (int i = 0; i < M; i++) {
        int t, x;
        cin >> t >> x;
        x--;
        if (t == 1) {
            update(x);
        } else {
            cout << query(x) << endl;
        }
    }
}