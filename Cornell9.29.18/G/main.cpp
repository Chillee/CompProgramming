#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

const int MAXN = 1e5 + 5;
int N, M;
vector<array<int, 3>> elist;
int par[MAXN];
int root(int v) { return par[v] < 0 ? v : (par[v] = root(par[v])); }
void merge(int x, int y) {
    if ((x = root(x)) == (y = root(y)))
        return;
    if (par[y] < par[x])
        swap(x, y);
    par[x] += par[y];
    par[y] = x;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int a, b, d;
        cin >> a >> b >> d;
        a--, b--;
        elist.push_back({a, b, d});
    }
    fill(par, par + MAXN, -1);
    for (int i = 0; i < elist.size(); i++) {
        if (elist[i][2] == 1)
            merge(elist[i][0], elist[i][1]);
    }
    int ans = 0;
    for (auto i : elist) {
        if (i[2] == 1)
            continue;
        if (par[i[0]] == par[i[1]])
            continue;
        merge(i[0], i[1]);
        ans++;
    }
    cout << (par[0] < 0 ? -par[0] : -par[par[0]]) << endl;
}