#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MOD = 1e9 + 7;
const ll MAXN = 1e5 + 5;

ll N, M;
ll V[MAXN];
vector<int> sccs[MAXN];

vector<ll> adj[MAXN];
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

int main() {
    cin >> N;
    for (ll i = 0; i < N; i++) {
        cin >> V[i];
    }
    cin >> M;
    for (ll i = 0; i < M; i++) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
    }
    scc.tarjans();
    for (int i = 0; i < N; i++) {
        sccs[scc.low[i]].push_back(i);
    }
    ll totalCost = 0;
    ll numSols = 1;
    for (int i = 0; i < N; i++) {
        auto scc = sccs[i];
        if (scc.size() == 0)
            continue;
        vector<ll> curCosts;
        for (auto i : scc) {
            curCosts.push_back(V[i]);
        }
        sort(curCosts.begin(), curCosts.end());
        totalCost += curCosts[0];
        if (curCosts.size() == 1) {
            continue;
        }
        ll cnt;
        for (cnt = 1; cnt < curCosts.size(); cnt++) {
            if (curCosts[cnt] != curCosts[0])
                break;
        }
        numSols = (numSols * cnt) % MOD;
    }
    cout << totalCost << ' ' << numSols << endl;
}