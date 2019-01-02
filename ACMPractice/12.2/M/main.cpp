#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10;
int N;
int adjm[MAXN][MAXN];
vector<int> adj[MAXN];
struct scc {
    const static int MAXV = MAXN;
    int num[MAXN], low[MAXV];
    bool curProcessing[MAXV];
    stack<int> curVis;
    int dfsCnt = 0;

    void dfs(int cur) {
        num[cur] = low[cur] = dfsCnt++;
        curProcessing[cur] = true;
        curVis.push(cur);
        for (auto v : adj[cur]) {
            if (num[v] == -1)
                dfs(v);
            if (curProcessing[v])
                low[cur] = min(low[cur], low[v]);
        }
        if (num[cur] == low[cur]) {
            while (curVis.top() != cur) {
                int t = curVis.top();
                curVis.pop();
                low[t] = low[cur];
                curProcessing[t] = false;
            }
            curVis.pop();
            curProcessing[cur] = false;
        }
    }
    void tarjans() {
        for (int i = 0; i < N; i++) {
            if (num[i] == -1)
                dfs(i);
        }
    }
};
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> adjm[i][j];
        }
    }
}