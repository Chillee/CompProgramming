#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

typedef long long ll;
const ll MAXN = 3e5 + 5;
const ll INF = 1e15 + 5;
ll N, M;
vector<array<ll, 2>> adjlist[MAXN];
ll X[MAXN];
ll pathIdx[MAXN];
ll pathLen[MAXN];
vector<ll> path;
set<ll> onPath;
ll maxD[MAXN];
bool vis[MAXN];
ll prv[MAXN];
void dfs(ll start, ll end, ll cur) {
    vis[cur] = true;
    if (cur == end) {
        return;
    }
    for (auto i : adjlist[cur]) {
        if (vis[i[0]])
            continue;
        prv[i[0]] = cur;
        dfs(start, end, i[0]);
    }
}
array<ll, 2> dfs2(ll cur, ll orig, ll curD) {
    if ((onPath.find(cur) != onPath.end() && cur != orig) || vis[cur])
        return {0, 0};
    vis[cur] = true;
    ll ans = curD;
    ll ans2 = 1;
    for (auto i : adjlist[cur]) {
        auto t = dfs2(i[0], orig, curD + i[1]);
        ans = max(ans, t[0]);
        ans2 += t[1];
    }
    return {ans, ans2};
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for (ll i = 0; i < N - 1; i++) {
        ll a, b, d;
        cin >> a >> b >> d;
        a--, b--;
        adjlist[a].push_back({b, d});
        adjlist[b].push_back({a, d});
    }
    for (ll i = 0; i < M; i++)
        cin >> X[i];
    fill(prv, prv + MAXN, -1);
    dfs(0, N - 1, 0);
    ll cur = N - 1;
    while (cur != -1) {
        path.push_back(cur);
        cur = prv[cur];
    }
    reverse(path.begin(), path.end());
    ll curDist = 0;
    for (ll i = 0; i < path.size(); i++) {
        onPath.insert(path[i]);
        pathIdx[path[i]] = i;
        if (i != 0) {
            for (auto j : adjlist[path[i]]) {
                if (j[0] == path[i - 1]) {
                    curDist += j[1];
                    break;
                }
            }
        }
        pathLen[path[i]] = curDist;
    }
    fill(vis, vis + MAXN, false);
    for (auto i : path) {
        auto res = dfs2(i, i, 0);
        maxD[i] = res[0];
        if (res[1] > 2) {
            for (int j = 0; j < M; j++) {
                cout << curDist << endl;
            }
            return 0;
        }
    }
    set<array<ll, 2>> curVals;
    for (auto i : path) {
        curVals.insert({pathLen[i] - maxD[i], i});
    }
    ll res = -INF;
    for (auto i : path) {
        while (curVals.size() > 0 && pathIdx[(*curVals.begin())[1]] <= pathIdx[i]) {
            curVals.erase(curVals.begin());
        }
        if (curVals.size() == 0)
            break;
        ll curMax = maxD[i];
        auto curVal = *curVals.begin();
        if (pathIdx[curVal[1]] == pathIdx[i] + 1 && maxD[curVal[1]] == 0 && maxD[i] == 0) {
            auto t = *curVals.begin();
            curVals.erase(curVals.begin());
            while (curVals.size() > 0 && pathIdx[(*curVals.begin())[1]] <= pathIdx[i]) {
                curVals.erase(curVals.begin());
            }
            if (curVals.size() == 0) {
                curVals.insert(t);
                continue;
            }
            curVal = *curVals.begin();
            curVals.insert(t);
        }
        ll curValMin = curVal[0];
        res = max(res, (curMax + pathLen[i] - curValMin));
    }
    for (ll i = 0; i < M; i++) {
        cout << min(curDist + res + X[i], curDist) << endl;
    }
}