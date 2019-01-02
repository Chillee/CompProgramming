#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;
int N, M;
vector<int> adjlist[MAXN];
int color[MAXN];
vector<int> components[MAXN];
void dfs(int cur, int clr) {
    if (color[cur] != -1)
        return;
    color[cur] = clr;
    for (auto i : adjlist[cur]) {
        dfs(i, clr);
    }
}

int main() {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adjlist[a].push_back(b);
        adjlist[b].push_back(a);
    }
    for (int i = 0; i < N; i++) {
        color[i] = -1;
    }
    for (int i = 0; i < N; i++) {
        if (color[i] == -1) {
            dfs(i, i);
        }
    }
    for (int i = 0; i < N; i++) {
        components[color[i]].push_back(i);
    }
    int res = 0;
    for (int i = 0; i < N; i++) {
        if (components[i].size() <= 1) {
            continue;
        }
        bool isCycle = true;
        for (auto j : components[i]) {
            if (adjlist[j].size() != 2) {
                isCycle = false;
                break;
            }
        }
        if (isCycle) {
            res++;
        }
    }
    cout << res << endl;
}