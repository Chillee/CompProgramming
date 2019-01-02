#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;
const int MAXY = 2005;
int T, N, P;
vector<array<int, 2>> segs[MAXY];
int dp[MAXY][MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin >> N >> P;
        int mxY = 0;
        for (int i = 0; i < MAXY; i++)
            segs[i].clear();
        for (int i = 0; i < N; i++) {
            int y, a, b;
            cin >> y >> a >> b;
            mxY = max(mxY, y);
            segs[y].push_back({a, b});
        }
        for (int i = 0; i < MAXY; i++)
            sort(segs[i].begin(), segs[i].end());
        for (int i = 0; i < MAXY; i++)
            for (int j = 0; j < MAXN; j++)
                dp[i][j] = 1e9 + 5;
        dp[0][0] = 0;
        int ans = 0;
        for (int i = 1; i <= mxY + 1; i++) {
            for (int j = 0; j <= N; j++) {
                dp[i][j] = dp[i - 1][j] + 1;
                for (int k = 1; k <= min((int)segs[i - 1].size(), j); k++) {
                    if (dp[i - 1][j - k] + segs[i - 1][k - 1][1] <= P)
                        ans = max(ans, j);

                    dp[i][j] = min(dp[i][j], dp[i - 1][j - k] + segs[i - 1][k - 1][1] * 2 + 1);
                }
            }
        }
        cout << ans << endl;
    }
}