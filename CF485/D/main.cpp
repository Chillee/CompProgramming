#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
const int INF = 1e8;
typedef pair<int, int> pii;

int N, M, S, K;
vector<int> adjlist[MAXN];
set<int> types[105];
int A[MAXN];
int colorDist[105][MAXN];

void dijkstra(int color) {
    vector<int> dist(N);
    queue<pii> pq;
    fill(dist.begin(), dist.end(), -1);
    for (auto i : types[color]) {
        pq.push({0, i});
    }
    while (!pq.empty()) {
        auto cur = pq.front();
        pq.pop();
        if (dist[cur.second] != -1)
            continue;
        dist[cur.second] = cur.first;
        for (auto i : adjlist[cur.second]) {
            pq.push({cur.first + 1, i});
        }
    }
    for (int i = 0; i < N; i++) {
        colorDist[color][i] = dist[i];
    }
}
int main() {
    cin >> N >> M >> K >> S;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        types[A[i]].insert(i);
    }
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adjlist[a].push_back(b);
        adjlist[b].push_back(a);
    }
    for (int i = 1; i <= K; i++) {
        dijkstra(i);
    }
    for (int i = 0; i < N; i++) {
        vector<int> cur;
        for (int j = 1; j <= K; j++) {
            cur.push_back(colorDist[j][i]);
        }
        sort(cur.begin(), cur.end());
        int res = 0;
        for (int i = 0; i < S; i++) {
            res += cur[i];
        }
        cout << res << ' ';
    }
}