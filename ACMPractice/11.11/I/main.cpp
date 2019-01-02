#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;
const int MAXK = 105;
int N, K;
int dp[MAXN][MAXK];
int A[MAXN];
int tinv[MAXN][MAXK];
int inv[MAXN][MAXK];
vector<int> pos;
bool valid[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        if (A[i] == 0) {
            pos.push_back(i);
        }
        valid[i] = true;
    }
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < K; j++) {
            tinv[i][j] = tinv[i - 1][j];
            if (A[i - 1] > j) {
                tinv[i][j]++;
            }
        }
    }
    int idx = 0;
    for (int i = 0; i < N; i++) {
        if (A[i] == 0) {
            for (int j = 0; j < K; j++) {
                inv[idx][j] = tinv[i][j];
            }
            idx++;
        }
    }
    for (int i = 1; i < idx; i++) {
        for (int j = K; j >= 0; j--) {
            for (int k = j + 1; k <= K; k++) {
                dp[i][j] = max(dp[i][j], dp[i - 1][k] + i + inv[i][j]);
            }
            // dp[i][j] = max(dp[i][j], dp[i-1])
        }
    }
}