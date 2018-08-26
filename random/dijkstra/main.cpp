#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
const int INF = 1 << 30;
int N, M;

typedef array<int, 2> pii;
vector<pii> adjlist[MAXN];
int dist[MAXN];
void dijkstra(int start) {
    fill(dist, dist + MAXN, INF);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, start});
    while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();
        if (dist[cur[1]] <= cur[0])
            continue;
        dist[cur[1]] = cur[0];
        for (auto i : adjlist[cur[1]]) {
            pq.push({i[0] + cur[0], i[1]});
        }
    }
}

int main() {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int a, b, d;
        cin >> a >> b >> d;
        a--, b--;
        adjlist[a].push_back({d, b});
        adjlist[b].push_back({d, a});
    }
    dijkstra(0);
    for (int i = 0; i < N; i++) {
        cout << dist[i] << ' ';
    }
    cout << endl;
    // cout << dist[5] << endl;
}