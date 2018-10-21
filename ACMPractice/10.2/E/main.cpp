#include <bits/stdc++.h>

// #define endl '\n';
using namespace std;

const int MAXN = 16;
const int MAXBIT = (1 << MAXN);
const int INF = 1e9 + 5;
int T, N;
int grid[MAXN][MAXN];
int dp[MAXN][MAXBIT];
int sos[MAXBIT];
bool isValid(bitset<MAXN> b) {
    for (int j = 1; j < N; j++) {
        if (b[j] && b[j - 1])
            return false;
    }
    return true;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin >> N;
        for (int i = 0; i < MAXN; i++) {
            fill(begin(grid[i]), end(grid[i]), 0);
            fill(begin(dp[i]), end(dp[i]), -INF);
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> grid[i][j];
            }
        }
        for (int i = 0; i < N; i++) {
            if (i == 0) {
                fill(sos, sos + MAXBIT, 0);
            } else {
                for (int j = 0; j < (1 << N); j++)
                    sos[j] = dp[i - 1][j];
                for (int j = 0; j < N; j++) {
                    for (int mask = 0; mask < (1 << N); mask++) {
                        if (mask & (1 << j))
                            sos[mask] = max(sos[mask], sos[mask ^ (1 << j)]);
                    }
                }
            }
            for (int j = 0; j < (1 << N); j++) {
                if (!isValid(j))
                    continue;
                bitset<MAXN> bs(j);
                int sm = 0;
                for (int k = 0; k < N; k++) {
                    if (bs[k])
                        sm += grid[i][k];
                }
                int mask = 0;
                bitset<MAXN> curVal;
                for (int k = 0; k < N; k++) {
                    if (bs[k] || (k > 0 && bs[k - 1]) || (k < N - 1 && bs[k + 1])) {
                        continue;
                    } else {
                        mask |= (1 << k);
                    }
                }
                dp[i][j] = sos[mask] + sm;
            }
        }
        int ans = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < MAXBIT; j++)
                ans = max(ans, dp[i][j]);
        }
        cout << ans << endl;
    }
}