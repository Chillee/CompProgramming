#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1001113;
ll P;
ll K, N, V;
ll dp[105][105];

int main() {
    dp[0][0] = 1;
    for (ll i = 1; i < 105; i++) {
        for (ll j = 0; j < 105; j++) {
            if (j != 0) {
                dp[i][j] = (dp[i - 1][j - 1] * (i - j) + dp[i][j]) % MOD;
            }
            dp[i][j] = (dp[i][j] + dp[i - 1][j] * (j + 1)) % MOD;
        }
    }
    cin >> P;
    for (ll p = 0; p < P; p++) {
        cin >> K >> N >> V;
        cout << K << " " << dp[N][V] << endl;
    }
}