#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
const int MAXN = 1e5 + 5;
int N, K;
vector<pii> adjlist[MAXN];
int degrees[MAXN];
int dist[MAXN];

int binSearch(int l, int r) {
    if (l == r - 1) {
        return r;
    }
    int mid = (l + r) / 2;
    queue<pii> Q;
    for (int i = 0; i < N; i++) {
        degrees[i] = adjlist[i].size();
        if (degrees[i] == 1) {
            degrees[i]--;
            Q.push({mid - adjlist[i][0].second, adjlist[i][0].first});
        }
    }
    fill(dist, dist + N, 1e9 + 5);
    while (!Q.empty()) {
        auto cur = Q.front();
        Q.pop();
        degrees[cur.second]--;
        dist[cur.second] = min(dist[cur.second], cur.first);
        if (degrees[cur.second] == 1) {
            for (auto i : adjlist[cur.second]) {
                if (degrees[i.first] > 0) {
                    if (dist[cur.second] - i.second < 0) {
                        break;
                    }
                    Q.push({dist[cur.second] - i.second, i.first});
                    degrees[cur.second]--;
                    break;
                }
            }
        }
    }
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (degrees[i] > 0) {
            count++;
        }
        if (degrees[i] > 2) {
            return binSearch(mid, r);
        }
    }
    if (count > K) {
        return binSearch(mid, r);
    }
    return binSearch(l, mid);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;
    for (int i = 0; i < N - 1; i++) {
        int a, b, d;
        cin >> a >> b >> d;
        a--, b--;
        adjlist[a].push_back({b, d});
        adjlist[b].push_back({a, d});
    }
    cout << binSearch(-1, 1e9 + 5) << endl;
    // cout << binSearch(4, 12) << endl;
}