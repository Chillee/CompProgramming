#pragma GCC optimize("O3")
#include <bits/stdc++.h>

#define all(x) x.begin(), x.end()
using namespace std;

typedef long long ll;
const ll MAXN = 2e5 + 5;
const ll INF = 1e18 + 5;
const ll MOD = 1e9 + 7;
ll N, M;
vector<array<ll, 3>> adj[MAXN];
ll dist[MAXN];
ll cnt[MAXN];
ll mxF[MAXN], mnF[MAXN];
void dijkstra(ll start) {
    fill(begin(dist), end(dist), INF);
    fill(begin(mnF), end(mnF), INF);
    priority_queue<array<ll, 3>, vector<array<ll, 3>>, greater<array<ll, 3>>> pq;
    pq.push({0, start, 0});
    cnt[start] = 1;
    mxF[start] = 0;
    mnF[start] = 0;
    while (!pq.empty()) {
        auto t = pq.top();
        ll prv = t[2], cur = t[1], d = t[0];
        pq.pop();
        if (dist[cur] < d)
            continue;
        if (cur != 0) {
            cnt[cur] += cnt[prv];
            cnt[cur] %= MOD;
            mxF[cur] = max(mxF[prv] + 1, mxF[cur]);
            mnF[cur] = min(mnF[prv] + 1, mnF[cur]);
        }
        if (dist[cur] == d)
            continue;

        dist[cur] = d;
        for (auto i : adj[t[1]])
            pq.push({t[0] + i[0], i[1], cur});
    }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for (ll i = 0; i < M; i++) {
        ll a, b, d;
        cin >> a >> b >> d;
        a--, b--;
        adj[a].push_back({d, b});
    }
    dijkstra(0);
    // for (ll i = 0; i < N; i++) {
    //     cout << i << ": " << dist[i] << ' ' << cnt[i] << ' ' << mnF[i] << ' ' << mxF[i] << endl;
    // }
    cout << dist[N - 1] << ' ' << cnt[N - 1] << ' ' << mnF[N - 1] << ' ' << mxF[N - 1] << endl;
}