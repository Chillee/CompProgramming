#include <bits/stdc++.h>

using namespace std;

int clr[100005];
int N;
vector<int> adj[100005];
bool vis[100005];
long long res[100005];
long long cnt = 0;

map<int, int> scores[100005];

void dfs(int cur) {
    if (vis[cur]) {
        return;
    }
    vis[cur] = true;
    for (int i = 0; i < adj[cur].size(); i++) {
        if (vis[adj[cur][i]]) {
            continue;
        }
        dfs(adj[cur][i]);
        for (auto &k : scores[adj[cur][i]]) {
            scores[cur][k.first] += k.second;
        }
        scores[adj[cur][i]].clear();
    }
    scores[cur][clr[cur]]++;
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> clr[i];
    }
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(0);
    for (int i = 0; i < N; i++) {
        long long score = 0;
        int mx = -1;
        for (auto &i : scores[i]) {
            if (i.second > mx) {
                score = i.first;
                mx = i.second;
            } else if (i.second == mx) {
                score += i.first;
            }
        }
        cout << score << ' ';
    }
}