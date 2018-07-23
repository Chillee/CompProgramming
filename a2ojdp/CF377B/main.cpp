#include <bits/stdc++.h>

using namespace std;

// dp[i][j] = minimum number of people to have first i satisfied, and j on the last day.
const int MAXN = 505;
const int INF = 1 << 30;
int N, K, A[MAXN];
int dp[MAXN][MAXN * 2];
int prv[MAXN][MAXN * 2];
int main() {
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            dp[i][j] = INF;
        }
    }
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    dp[0][A[0]] = 0;
    for (int i = 1; i < N; i++) {
        for (int j = A[i]; j < MAXN; j++) {
            for (int k = 0; k < MAXN; k++) {
                if (j + k >= K) {
                    int t = dp[i - 1][k] + j - A[i];
                    if (t < dp[i][j]) {
                        prv[i][j] = k;
                        dp[i][j] = t;
                    }
                }
            }
        }
    }
    for (int i = 0; i <= K; i++) {
        if (dp[N - 1][i] < INF) {
            cout << dp[N - 1][i] << endl;
            vector<int> res;
            int cur = i;
            for (int j = N - 1; j >= 0; j--) {
                res.push_back(cur);
                cur = prv[j][cur];
            }
            reverse(res.begin(), res.end());
            for (auto j : res) {
                cout << j << ' ';
            }
            cout << endl;
            break;
        }
    }
    // for (int i = 0; i < N; i++) {
    //     for (int j = 0; j < 10; j++) {
    //         cout << dp[i][j] << ' ';
    //     }
    //     cout << endl;
    // }
}