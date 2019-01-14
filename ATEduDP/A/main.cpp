#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
int N, H[MAXN];
int dp[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> H[i];
    dp[1] = abs(H[1] - H[0]);
    for (int i = 2; i < N; i++) {
        dp[i] = min(dp[i - 2] + abs(H[i] - H[i - 2]), dp[i - 1] + abs(H[i] - H[i - 1]));
    }
    cout << dp[N - 1] << endl;
}