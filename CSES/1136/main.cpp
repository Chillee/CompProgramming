#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;
int N, M;
vector<int> adj[MAXN];
set<int> endp[MAXN];
int ans[MAXN];
set<int> *dfs(int cur, int p) {
    vector<set<int> *> curp = {&endp[cur]};
    for (auto i : adj[cur]) {
        if (i == p)
            continue;
        curp.push_back(dfs(i, cur));
    }
    sort(curp.begin(), curp.end(), [](set<int> *a, set<int> *b) { return a->size() > b->size(); });
    for (int i = 1; i < curp.size(); i++) {
        for (auto j : *curp[i]) {
            if (curp[0]->find(j) != curp[0]->end()) {
                ans[cur]++;
                curp[0]->erase(j);
            } else {
                curp[0]->insert(j);
            }
        }
    }
    ans[cur] += curp[0]->size();
    return curp[0];
}

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
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        if (a == b)
            ans[a]++;
        else {
            endp[a].insert(i);
            endp[b].insert(i);
        }
    }
    dfs(0, 0);
    for (int i = 0; i < N; i++)
        cout << ans[i] << ' ';
    cout << endl;
}