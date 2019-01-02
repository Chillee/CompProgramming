#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAXBALANCE = 101 * 101 * 10 * 2;
const ll OFFSET = (100 * 100 * 10) / 2;
ll dp[105][MAXBALANCE];
ll N, K;
ll taste[105];
ll cal[105];

int main() {
    cin >> N >> K;
    for (ll i = 0; i < N; i++) {
        cin >> taste[i];
    }
    for (ll i = 0; i < N; i++) {
        cin >> cal[i];
        cal[i] *= K;
    }
    for (ll i = 0; i < N; i++) {
        for (ll j = 0; j < MAXBALANCE; j++) {
            dp[i][j] = -(1 << 30);
        }
    }
    dp[0][OFFSET] = 0;
    for (ll i = 1; i <= N; i++) {
        for (ll j = 0; j < MAXBALANCE; j++) {
            ll bal = (taste[i - 1] - cal[i - 1]);
            if (j - bal < 0) {
                continue;
            }
            if (dp[i - 1][j] >= dp[i - 1][j - bal] + taste[i - 1]) {
                dp[i][j] = dp[i - 1][j];
            } else {
                // cout << "YO" << endl;
                dp[i][j] = dp[i - 1][j - bal] + taste[i - 1];
            }
        }
    }
    // for (ll i = 0; i <= N; i++) {

    //     for (ll j = OFFSET - 10; j < OFFSET + 10; j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    if (dp[N][OFFSET] == 0) {
        cout << -1 << endl;
    } else {
        cout << dp[N][OFFSET] << endl;
    }
}