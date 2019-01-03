#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2005;
const int T = 31 - __builtin_clz(MAXN);
int N;
int adj[MAXN][MAXN];
template <int MAXN> struct SCC {
    int num[MAXN], low[MAXN];
    bool curProcessing[MAXN];
    stack<int> curVis;
    int dfsCnt = 0;
    SCC() { fill(begin(num), end(num), -1), fill(begin(low), end(low), -1); }
    void tarjans(int cur) {
        num[cur] = low[cur] = dfsCnt++;
        curProcessing[cur] = true;
        curVis.push(cur);
        for (int i = 0; i < N; i++) {
            if (adj[cur][i] == 0)
                continue;
            if (num[i] == -1)
                tarjans(i);
            if (curProcessing[i])
                low[cur] = min(low[cur], low[i]);
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
};
SCC<MAXN> scc;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> adj[i][j];
    scc.tarjans(0);
    int cur = scc.low[0];

    for (int i = 0; i < N; i++) {
        if (scc.low[i] != cur) {
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;
}