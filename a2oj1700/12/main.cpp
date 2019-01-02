#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MOD = 1e9 + 7;
const ll MAXN = 1e5 + 5;

ll N, M;
ll V[MAXN];
ll dfsCnt = 0;
vector<int> sccs[MAXN];

vector<ll> adj[MAXN];
int num[MAXN], low[MAXN];
bool isProcess[MAXN];
stack<int> curVis;

void tarjans(int cur) {
    num[cur] = low[cur] = dfsCnt++;
    isProcess[cur] = true;
    curVis.push(cur);
    for (auto i : adj[cur]) {
        if (num[i] == -1)
            tarjans(i);
        if (isProcess[i])
            low[cur] = min(low[cur], low[i]);
    }
    if (num[cur] == low[cur]) {
        int t = -1;
        while (t != cur) {
            t = curVis.top();
            curVis.pop();
            low[t] = num[cur];
            isProcess[t] = false;
        }
    }
}

int main() {
    fill(num, num + MAXN, -1);
    fill(low, low + MAXN, -1);
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
    for (ll i = 0; i < N; i++) {
        if (num[i] == -1)
            tarjans(i);
    }
    for (int i = 0; i < N; i++) {
        sccs[low[i]].push_back(i);
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