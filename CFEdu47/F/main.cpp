#include <bits/stdc++.h>

using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

#define endl '\n'
const int RANDOM = (long long)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
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

const int MAXN = 1e6 + 5;
int N;
vector<int> adj[MAXN];
struct info {
    gp_hash_table<int, int, chash> vals;
    int offset;
    int mxIdx;
};
info dp[MAXN];
int ans[MAXN];
void add(info &x, info &a, int k) {
    int diff = x.offset - a.offset;
    x.vals[k - diff] += a.vals[k];
    if (x.vals[k - diff] > x.vals[x.mxIdx]) {
        x.mxIdx = k - diff;
    } else if (x.vals[k - diff] == x.vals[x.mxIdx] && k - diff < x.mxIdx) {
        x.mxIdx = k - diff;
    }
}
info *dfs(int cur, int p) {
    vector<info *> res = {&dp[cur]};
    for (auto i : adj[cur]) {
        if (i == p)
            continue;
        res.push_back(dfs(i, cur));
    };
    for (int i = 1; i < res.size(); i++) {
        if (res[0]->vals.size() < res[i]->vals.size())
            swap(res[0], res[i]);
    }
    for (int i = 1; i < res.size(); i++) {
        for (auto j : res[i]->vals) {
            add(*res[0], *res[i], j.first);
        }
    }
    ans[cur] = res[0]->mxIdx + res[0]->offset;
    res[0]->offset++;
    return res[0];
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 0; i < N; i++) {
        dp[i].vals[0] = 1;
        dp[i].offset = 0;
        dp[i].mxIdx = 0;
    }
    dfs(0, 0);
    for (int i = 0; i < N; i++) {
        cout << ans[i] << endl;
    }
}