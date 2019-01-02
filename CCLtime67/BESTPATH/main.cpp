#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e3 + 5;
const int INF = 1e9 + 5;
int T, N, M;
// vector<array<int, 3>> edges;
vector<array<int, 2>> adj[MAXN];
vector<array<int, 2>> radj[MAXN];
int cnt[MAXN];

int dist[MAXN], rdist[MAXN];
bool spfa(int start) {
    // cout << start << endl;
    fill(dist, dist + N, INF);
    fill(rdist, rdist + N, INF);
    dist[start] = 0;
    rdist[start] = 0;
    queue<int> q;
    fill(cnt, cnt + N, 0);
    q.push(start);
    cnt[start]++;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (auto i : adj[cur]) {
            if (dist[cur] + i[0] < dist[i[1]]) {
                dist[i[1]] = dist[cur] + i[0];
                cnt[i[1]]++;
                if (cnt[i[1]] >= N)
                    return true;
                q.push(i[1]);
            }
        }
    }
    q = queue<int>{};
    q.push(start);
    fill(cnt, cnt + N, 0);
    cnt[start]++;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (auto i : radj[cur]) {
            if (rdist[cur] + i[0] < rdist[i[1]]) {
                rdist[i[1]] = rdist[cur] + i[0];
                cnt[i[1]]++;
                if (cnt[i[1]] >= N)
                    return true;
                q.push(i[1]);
            }
        }
    }
    return false;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int t = 0; t < T; t++) {
        int N, M;
        cin >> N >> M;
        for (int i = 0; i < M; i++) {
            int a, b, d;
            cin >> a >> b >> d;
            a--, b--;
            adj[a].push_back({d, b});
            radj[b].push_back({d, a});
        }
        for (int i = 0; i < N; i++) {
            bool res = spfa(i);
            if (res) {
                cout << "INF" << endl;
                continue;
            }
            int mn1 = 0, mn2 = 0;
            for (int j = 0; j < N; j++) {
                mn1 = min(dist[j], mn1);
                mn2 = min(rdist[j], mn2);
            }
            cout << mn1 + mn2 << endl;
        }
    }
}