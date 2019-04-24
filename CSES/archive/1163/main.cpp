#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;
int X, N;
int P[MAXN];
array<int, 2> diffs[MAXN];
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
Dsu<MAXN> dsu;
int mapping[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> X >> N;
    for (int i = 0; i < N; i++)
        cin >> P[i];
    for (int i = 0; i < N; i++)
        diffs[i] = {P[i], i};
    diffs[N] = {X, -1};
    sort(diffs, diffs + N + 1);
    for (int i = N; i > 0; i--) {
        if (i == 0)
            diffs[i] = {diffs[i][0], diffs[i][1]};
        else
            diffs[i] = {diffs[i][0] - diffs[i - 1][0], diffs[i][1]};
    }
    for (int i = 0; i < N; i++)
        mapping[diffs[i][1]] = i;

    dsu.init(N + 1);
    for (int i = 0; i <= N; i++)
        dsu.sz[i] = diffs[i][0];
    vector<int> ans;
    int mx = 0;
    for (int i = 0; i <= N; i++)
        mx = max(dsu.sz[i], mx);
    for (int i = N - 1; i >= 0; i--) {
        ans.push_back(mx);
        dsu.merge(mapping[i], mapping[i] + 1);
        mx = max(dsu.sz[dsu.root(mapping[i])], mx);
    }
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < N; i++)
        cout << ans[i] << ' ';
    cout << endl;
}