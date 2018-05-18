#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
const int INF = 1 << 30;
int N, M;

vector<pair<int, int>> adjlist[MAXN];
int dist[MAXN];
void dijkstra(int start) {
    fill(dist, dist + N, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});
    while (!pq.empty()) {
        auto t = pq.top();
        pq.pop();
        if (dist[t.second] <= t.first)
            continue;
        dist[t.second] = t.first;
        for (auto i : adjlist[t.second]) {
            pq.push({t.first + i.second, i.first});
        }
    }
}

int main() {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int a, b, d;
        cin >> a >> b >> d;
        a--, b--;
        adjlist[a].push_back({b, d});
        adjlist[b].push_back({a, d});
    }
    dijkstra(0);
    for (int i = 0; i < N; i++) {
        cout << dist[i] << ' ';
    }
    cout << endl;
    // cout << dist[5] << endl;
}