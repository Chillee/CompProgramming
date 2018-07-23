#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 1000;
const ll MOD = 1e9 + 7;
ll T, N;
ll dp[MAXN][3];
char grid[MAXN][3];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    cin >> T;
    for (ll t = 1; t <= T; t++) {
        cin >> N;
        for (ll i = 0; i < MAXN; i++) {
            for (ll j = 0; j < 3; j++) {
                dp[i][j] = 0;
            }
        }
        for (ll i = 0; i < 3; i++) {
            for (ll j = 0; j < N; j++) {
                cin >> grid[j][i];
            }
        }
        if (grid[0][0] == '.') {
            dp[0][0] = 1;
        }
        for (ll i = 1; i < N; i++) {
            if (grid[i][0] == '.' && grid[i - 1][0] == '.') {
                dp[i][0] = dp[i - 1][1];
            }
            if (grid[i][2] == '.' && grid[i - 1][2] == '.') {
                dp[i][2] = dp[i - 1][1];
            }
            if (grid[i][1] == '.' && grid[i - 1][1] == '.') {
                dp[i][1] = (dp[i - 1][0] + dp[i - 1][2]) % MOD;
            }
        }
        cout << "Case #" << t << ": " << dp[N - 1][1] << endl;
    }
}