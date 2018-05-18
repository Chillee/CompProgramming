#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAXN = 1e5 + 5;
ll N;
vector<ll> adjlist[MAXN];
ll par[MAXN];
ll V[MAXN];
ll res;

void root(ll cur) {
    for (auto i : adjlist[cur]) {
        if (par[i] != -1) {
            continue;
        }
        par[i] = cur;
        root(i);
    }
}
pair<ll, ll> calc(ll cur) {
    ll pos = 0;
    ll neg = 0;
    for (auto i : adjlist[cur]) {
        if (i == par[cur])
            continue;
        auto ops = calc(i);
        pos = max(ops.first, pos);
        neg = max(ops.second, neg);
    }
    V[cur] += pos - neg;
    if (V[cur] > 0) {
        neg += V[cur];
    } else {
        pos += abs(V[cur]);
    }
    return {pos, neg};
}

int main() {
    cin >> N;
    for (ll i = 0; i < N - 1; i++) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        adjlist[a].push_back(b);
        adjlist[b].push_back(a);
    }
    for (ll i = 0; i < N; i++) {
        cin >> V[i];
    }
    fill(par, par + N, -1);
    par[0] = 0;
    root(0);
    auto res = calc(0);
    cout << res.first + res.second << endl;
}