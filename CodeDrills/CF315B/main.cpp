#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 4005;
const ll MOD = 1e9 + 7;

ll N;
ll dp[MAXN][MAXN];
int main() {
    cin >> N;
    dp[0][0] = 1;
    for (ll i = 1; i <= N; i++) {
        for (ll j = 1; j <= N; j++) {
            dp[i][j] = (j * dp[i - 1][j] + dp[i - 1][j - 1]) % MOD;
        }
    }
    ll ans = 0;
    for (ll i = 0; i <= N; i++) {
        ans = (dp[N][i] * i + ans) % MOD;
    }
    cout << ans << endl;
}