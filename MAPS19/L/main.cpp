#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;
int N;
char grid[MAXN][MAXN];
vector<array<int, 2>> spies, houses;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'S') {
                spies.push_back({i, j});
            } else if (grid[i][j] == 'H') {
                houses.push_back({i, j});
            }
        }
    }
    int ans = 0;
    for (auto i : spies) {
        int cur = 1e9 + 5;
        for (auto j : houses) {
            cur = min(cur, abs(i[0] - j[0]) + abs(i[1] - j[1]));
        }
        ans = max(cur, ans);
    }
    cout << ans << endl;
}