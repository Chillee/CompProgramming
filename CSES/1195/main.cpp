#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 2e5 + 5;
const ll INF = 1e18 + 5;
ll N, M;
vector<array<ll, 2>> adj[MAXN];
ll dist[MAXN][2];
ll dijkstra(ll s, ll t) {
    for (int i = 0; i < MAXN; i++)
        dist[i][0] = INF, dist[i][1] = INF;
    priority_queue<array<ll, 3>, vector<array<ll, 3>>, greater<array<ll, 3>>> pq;
    pq.push({0, s, 0});
    while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();
        if (cur[2] > 1 || cur[0] >= dist[cur[1]][cur[2]])
            continue;
        dist[cur[1]][cur[2]] = cur[0];
        for (auto i : adj[cur[1]]) {
            pq.push({cur[0] + i[1], i[0], cur[2]});
            pq.push({cur[0] + i[1] / 2, i[0], cur[2] + 1});
        }
    }
    return dist[t][1];
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for (ll i = 0; i < M; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        adj[a].push_back({b, c});
    }
    cout << dijkstra(0, N - 1) << endl;
}