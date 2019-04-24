#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;
int N, Q;
int nxt[MAXN];
int cycIndex[MAXN], cycSize[MAXN];
vector<int> adj[MAXN], radj[MAXN];
bool sing[MAXN];
array<int, 2> distToCyc[MAXN];
int tin[MAXN], tout[MAXN];
bool vis[MAXN];
template <int MAXN> struct SCC {
    int num[MAXN], low[MAXN];
    bool curProcess[MAXN];
    stack<int> curVis;
    int dfsCnt = 0;
    SCC() { fill(begin(num), end(num), -1), fill(begin(low), end(low), -1); }
    void dfs(int cur) {
        num[cur] = low[cur] = dfsCnt++;
        curProcess[cur] = true;
        curVis.push(cur);
        for (auto v : adj[cur]) {
            if (num[v] == -1)
                dfs(v);
            if (curProcess[v])
                low[cur] = min(low[cur], low[v]);
        }
        if (num[cur] == low[cur]) {
            while (curVis.top() != cur) {
                int t = curVis.top();
                curVis.pop();
                low[t] = low[cur];
                curProcess[t] = false;
            }
            curVis.pop();
            curProcess[cur] = false;
        }
    }
    void tarjans() {
        for (int i = 0; i < N; i++)
            if (num[i] == -1)
                dfs(i);
    }
};
SCC<MAXN> scc;
void dfs(int cur, int d, set<int> &curD) {}
int cycleCnt(int cur, int orig, int d) {
    if (cur == orig)
        return 1;
    cycIndex[cur] = d++;
    return 1 + cycleCnt(nxt[cur], orig, d);
}
int timer = 0;
void revCnt(int cur, int cyc, int d = 0) {
    distToCyc[cur] = {d, cyc};
    tin[cur] = timer++;
    for (auto i : radj[cur]) {
        if (cycIndex[i] == -1)
            revCnt(i, cyc, d + 1);
    }
    tout[cur] = timer++;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> Q;
    for (int i = 0; i < N; i++) {
        cin >> nxt[i];
        nxt[i]--;
        if (nxt[i] == i) {
            sing[i] = true;
            continue;
        }
        adj[i].push_back(nxt[i]);
        radj[nxt[i]].push_back(i);
    }
    scc.tarjans();
    fill(cycIndex, cycIndex + MAXN, -1);
    for (int i = 0; i < MAXN; i++) {
        distToCyc[i][1] = i;
    }
    for (int i = 0; i < N; i++) {
        if (scc.low[i] == scc.num[i] || cycIndex[i] != -1)
            continue;
        cycIndex[i] = 0;
        cycSize[scc.low[i]] = cycleCnt(nxt[i], i, 1);
    }
    for (int i = 0; i < N; i++) {
        if (cycIndex[i] == -1 && !sing[i])
            continue;
        timer = 0;
        revCnt(i, i);
    }
    for (int i = 0; i < Q; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        if (cycIndex[a] == -1 && cycIndex[b] == -1) {
            if (distToCyc[a][1] != distToCyc[b][1] || (!(tin[b] <= tin[a] && tout[b] >= tout[a]) && !sing[a] && !sing[b]))
                cout << -1 << endl;
            else
                cout << max(-1, distToCyc[a][0] - distToCyc[b][0]) << endl;
            continue;
        } else if (cycIndex[a] != -1 && cycIndex[b] == -1) {
            cout << -1 << endl;
            continue;
        } else if (cycIndex[a] != -1 && cycIndex[b] != -1) {
            if (scc.low[a] == scc.low[b]) {
                int cycDist = (cycIndex[b] - cycIndex[a] + cycSize[scc.low[a]]) % cycSize[scc.low[a]];
                cout << cycDist << endl;
            } else {
                cout << -1 << endl;
            }
            continue;
        } else if (cycIndex[a] == -1 && cycIndex[b] != -1) {
            int cycNode = distToCyc[a][1];
            if (scc.low[cycNode] != scc.low[b]) {
                cout << -1 << endl;
                continue;
            }
            int cycDist = (cycIndex[b] - cycIndex[cycNode] + cycSize[scc.low[b]]) % cycSize[scc.low[b]];
            cout << distToCyc[a][0] + cycDist << endl;
        }
    }
}