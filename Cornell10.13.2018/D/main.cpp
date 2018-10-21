#include <bits/stdc++.h>

using namespace std;

const int MAXN = 19;
int N;
double grid[MAXN][MAXN];
double dp[1LL << MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
        }
    }
    dp[(1 << N) - 1] = 1;
    for (int i = (1 << N) - 1; i >= 0; i--) {
        bitset<MAXN> cur = i;
        int numBits = cur.count();
        int numComb = numBits * (numBits - 1) / 2;
        double curProb = dp[cur.to_ulong()];
        int cnt = 0;
        for (int j = 0; j < N; j++) {
            for (int k = j + 1; k < N; k++) {
                if (cur[j] && cur[k]) {
                    cnt++;
                    cur[j] = 1;
                    cur[k] = 0;
                    dp[cur.to_ulong()] += (curProb * grid[j][k]) * (1.0 / numComb);
                    cur[j] = 0;
                    cur[k] = 1;
                    dp[cur.to_ulong()] += curProb * grid[k][j] * (1.0 / numComb);
                    cur[j] = 1;
                    cur[k] = 1;
                }
            }
        }
        // cout << cnt << ' ' << numComb << endl;
        // assert(cnt == numComb);
    }
    for (int i = 0; i < N; i++) {
        cout << setprecision(12) << dp[1 << i] << ' ';
    }
    cout << endl;
}