#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
int N;
vector<pair<int, bool>> adjlist[MAXN];
int par[MAXN];
int type[MAXN];
void root(int cur) {
    for (auto i : adjlist[cur]) {
        if (par[cur] == i.first)
            continue;
        par[i.first] = cur;
        root(i.first);
    }
}
vector<int> ans;
bool dfs(int cur, bool parProblem) {
    bool childProblem = false;
    for (auto i : adjlist[cur]) {
        if (i.first == par[cur])
            continue;
        bool childHasProblem = dfs(i.first, i.second);
        childProblem = childProblem || childHasProblem || i.second;
    }
    if (!childProblem && parProblem) {
        ans.push_back(cur);
    }
    return childProblem;
}
int main() {
    cin >> N;
    for (int i = 0; i < N - 1; i++) {
        int a, b, t;
        cin >> a >> b >> t;
        a--, b--;
        adjlist[a].push_back({b, t == 2});
        adjlist[b].push_back({a, t == 2});
    }
    par[0] = 0;
    root(0);
    dfs(0, false);
    cout << ans.size() << endl;
    for (auto i : ans) {
        cout << i + 1 << endl;
    }
}