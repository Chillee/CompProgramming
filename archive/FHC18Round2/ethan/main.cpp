#include <bits/stdc++.h>

using namespace std;

int T, N, K;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cin >> N >> K;
        if (K == 1) {
            cout << "Case #" << t << ": " << 0 << endl;
            cout << 1 << endl;
            cout << 1 << ' ' << N << ' ' << 1 << endl;
            continue;
        }
        vector<array<int, 3>> edges;
        int curEdge = K - 1;
        int ans = 0;
        for (int i = 1; i < N; i++) {
            if (curEdge == 1) {
                edges.push_back({i, N, curEdge});
                ans += curEdge;
                break;
            }
            edges.push_back({i, i + 1, curEdge});
            ans += curEdge;
            curEdge--;
        }
        if (edges.size() > 1) {
            edges.push_back({1, N, K});
            cout << "Case #" << t << ": " << ans - K << endl;
        } else {
            cout << "Case #" << t << ": " << 0 << endl;
        }
        cout << edges.size() << endl;
        for (auto i : edges) {
            cout << i[0] << ' ' << i[1] << ' ' << i[2] << endl;
        }
    }
}