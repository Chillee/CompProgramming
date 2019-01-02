#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAXN = 200005;
const ll MAXM = 1005;
const ll MOD = 1e9 + 7;
vector<ll> adjlist[MAXN];
ll N, M;
bool red[MAXN];

vector<ll> dfs(ll cur) {
    vector<vector<ll>> dps;
    for (auto i : adjlist[cur]) {
        dps.push_back(dfs(i));
    }
    vector<ll> res;
    if (dps.size() == 0) {
        if (red[cur]) {
            res.resize(2);
            res[1] = 1;
        } else {
            res.resize(1);
            res[0] = 1;
        }
        return res;
    }
    res = dps[0];
    for (ll i = 1; i < dps.size(); i++) {
        res.resize(res.size() + dps[i].size() - 1);
        vector<ll> prev = res;
        for (ll j = 0; j < dps[i].size(); j++) {
            for (ll k = 0; k < res.size(); k++) {
                res[j + k] = (res[j + k] + (dps[i][j] * prev[k]) % MOD) % MOD;
            }
            res[j] = (res[j] + dps[i][j]) % MOD;
        }
    }
    if (red[cur]) {
        res.resize(max((ll)res.size(), 2LL));
        res[1] = (res[1] + 1) % MOD;
    } else {
        res[0] = (res[0] + 1) % MOD;
    }
    return res;
}

int main() {
    cin >> N >> M;
    for (ll i = 1; i < N; i++) {
        ll t;
        cin >> t;
        t--;
        adjlist[t].push_back(i);
    }
    for (ll i = 0; i < M; i++) {
        ll t;
        cin >> t;
        t--;
        red[t] = true;
    }
    auto ans = dfs(0);
    ans[0] += 1;
    ans[0] = ans[0] % MOD;
    ans.resize(M + 1);
    for (auto i : ans) {
        cout << i << endl;
    }
}