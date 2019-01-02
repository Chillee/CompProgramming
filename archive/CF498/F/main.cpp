#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int MAXN = 1e6 + 5;
int N;
vector<int> adjlist[MAXN];
vector<int> children[MAXN];
int par[MAXN];
void root(int cur) {
    for (auto i : adjlist[cur]) {
        if (i == par[cur])
            continue;
        children[cur].push_back(i);
        par[i] = cur;
        root(i);
    }
}
pair<set<pii>, int> dp(int cur) {
    set<pii> res;
    vector<set<pii>> results;
    int mxEl = 0;
    for (auto i : adjlist[cur]) {
        auto pairCur = dp(i);
        auto cur = pairCur.first;
        mxEl = max(mxEl, pairCur.second);
        results.push_back(cur);
    }
    for (auto i : results) {
        int curMx = i.rbegin()->first;
        for (auto j : i) {
            auto cur = res.lower_bound({j.first});
            res.insert()
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adjlist[a].push_back(b);
        adjlist[b].push_back(a);
    }
    par[0] = -1;
    root(0);
}