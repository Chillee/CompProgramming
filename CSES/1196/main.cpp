#pragma GCC optimize("O3")
#include <bits/stdc++.h>

#define all(x) x.begin(), x.end()
using namespace std;
typedef long long ll;

const ll INF = 1e18 + 5;
const ll MAXN = 2e5 + 5;
ll N, M, K;
vector<array<ll, 2>> adj[MAXN];
vector<ll> dist[MAXN];
void dijkstra(ll start) {
    priority_queue<array<ll, 2>, vector<array<ll, 2>>, greater<array<ll, 2>>> pq;
    pq.push({0, start});
    while (!pq.empty()) {
        auto t = pq.top();
        pq.pop();
        if (dist[t[1]].size() == K)
            continue;
        dist[t[1]].push_back(t[0]);
        for (auto i : adj[t[1]])
            pq.push({t[0] + i[0], i[1]});
    }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M >> K;
    for (ll i = 0; i < M; i++) {
        ll a, b, d;
        cin >> a >> b >> d;
        a--, b--;
        adj[a].push_back({d, b});
    }
    dijkstra(0);
    for (ll i = 0; i < K; i++)
        cout << dist[N - 1][i] << " ";

    cout << endl;
}
