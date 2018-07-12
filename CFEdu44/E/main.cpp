#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5e5 + 5;
int N, K, D;
int pencils[MAXN];
int dp[MAXN];
int main() {
    cin >> N >> K >> D;
    for (int i = 0; i < N; i++) {
        cin >> pencils[i];
    }
    if (K == 1) {
        cout << "YES" << endl;
        return 0;
    }
    sort(pencils, pencils + N);
    fill(dp, dp + MAXN, -1e9);
    int curLow = 0;
    for (int i = 1; i < N; i++) {
        if (abs(dp[i - 1] - pencils[i]) <= D) {
            dp[i] = max(dp[i], dp[i - 1]);
        }
        if (i - K + 1 >= 0 && (i - K == -1 || dp[i - K] > 0) && abs(pencils[i - K + 1] - pencils[i]) <= D) {
            dp[i] = max(dp[i], pencils[i - K + 1]);
        }
    }
    // for (int i = 0; i < N; i++) {
    //     cout << dp[i] << ' ';
    // }
    // cout << endl;
    if (dp[N - 1] > 0) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}