#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5e4 + 5;
const int INF = 1e9 + 5;
int N, M, K;
int yum[MAXN];
vector<array<int, 2>> adj[MAXN];
int dist[MAXN], dist2[MAXN];
void dijkstra(int start) {
    fill(begin(dist), end(dist), INF);
    priority_queue<array<int, 2>, vector<array<int, 2>>, greater<array<int, 2>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        auto t = pq.top();
        pq.pop();
        if (dist[t[1]] <= t[0])
            continue;
        dist[t[1]] = t[0];
        for (auto i : adj[t[1]]) {
            pq.push({t[0] + i[0], i[1]});
        }
    }
}
void dijkstra2() {
    priority_queue<array<int, 2>, vector<array<int, 2>>, greater<array<int, 2>>> pq;
    for (int i = 0; i < N; i++) {
        if (yum[i] > 0) {
            pq.push({dist[i] - yum[i], i});
        }
    }
    fill(begin(dist2), end(dist2), INF);

    while (!pq.empty()) {
        auto t = pq.top();
        pq.pop();
        if (dist2[t[1]] <= t[0])
            continue;
        dist2[t[1]] = t[0];
        for (auto i : adj[t[1]]) {
            pq.push({t[0] + i[0], i[1]});
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("dining.in", "r", stdin);
    // freopen("dining.out", "w", stdout);
    cin >> N >> M >> K;
    for (int i = 0; i < M; i++) {
        int a, b, t;
        cin >> a >> b >> t;
        a--, b--;
        adj[a].push_back({t, b});
        adj[b].push_back({t, a});
    }
    for (int i = 0; i < K; i++) {
        int x, t;
        cin >> x >> t;
        x--;
        yum[x] = t;
    }
    dijkstra(N - 1);
    dijkstra2();
    for (int i = 0; i < N - 1; i++) {
        cout << (dist2[i] <= dist[i]) << endl;
    }
    cout << endl;
}