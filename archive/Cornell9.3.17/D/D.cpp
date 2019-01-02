#include <bits/stdc++.h>

using namespace std;

typedef long double ld;
const int MAXN = 100005;

int N;
vector<int> adj[MAXN];
int subtree[MAXN];
long double res[MAXN];

void dfs(int cur, ld time) {
    res[cur] = time;
    double total = 0;
    for (auto i : adj[cur]) {
        if (i == cur) {
            continue;
        }
        total += subtree[i];
    }
    if (adj[cur].size() == 1) {
        dfs(adj[cur][0], time + 1);
        return;
    }
    for (auto i : adj[cur]) {
        double new_time = 0;
        new_time = ((total-subtree[i])/adj[cur].size())*(adj[cur].size()/2.0);
        // for (int j = 0; j < adj[cur].size(); j++) {
        //     if (j == 0) {
        //     } else {
        //         new_time += (1.0 / (adj[cur].size())) * (total - subtree[i]) * (j / (adj[cur].size() - 1.0));
        //     }
        // }
        dfs(i, time + new_time + 1);
    }
}
int treesize(int cur) {
    int size = 1;
    for (auto i : adj[cur]) {
        if (i == cur) {
            continue;
        }
        size += treesize(i);
    }
    subtree[cur] = size;
    return size;
}
int main() {
    cin >> N;
    for (int i = 1; i < N; i++) {
        int a;
        cin >> a;
        a--;
        adj[a].push_back(i);
    }
    treesize(0);

    dfs(0, 1);
    for (int i = 0; i < N; i++) {
        cout << res[i] << ' ';
    }
}