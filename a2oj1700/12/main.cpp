#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MOD = 1e9 + 7;
const ll MAXN = 1e5 + 5;

ll N, M;
ll V[MAXN];
ll dfsCnt = 0;
vector<int> sccs[MAXN];

vector<ll> adjlist[MAXN];
ll num[MAXN], low[MAXN];
bool curProcessing[MAXN];
stack<ll> curVis;

void tarjans(ll cur) {
    num[cur] = low[cur] = dfsCnt++;
    curProcessing[cur] = true;
    curVis.push(cur);
    for (auto v : adjlist[cur]) {
        if (num[v] == -1)
            tarjans(v);
        if (curProcessing[v])
            low[cur] = min(low[cur], low[v]);
    }
    if (num[cur] == low[cur]) {
        while (curVis.top() != cur) {
            ll t = curVis.top();
            curVis.pop();
            low[t] = low[cur];
            curProcessing[t] = false;
        }
        curVis.pop();
        curProcessing[cur] = false;
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
        adjlist[a].push_back(b);
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