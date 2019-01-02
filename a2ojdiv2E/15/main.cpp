#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll T;
string S;
const ll MAXCHAR = 26;
const ll MAXN = 105;
const ll MOD = 1e9 + 7;
ll dp[MAXN][MAXCHAR * MAXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (ll i = 0; i < 26; i++) {
        dp[0][i] = 1;
    }
    for (ll i = 1; i < MAXN; i++) {
        for (ll j = 0; j < MAXCHAR * MAXN; j++) {
            for (ll k = max(0LL, j - 26 + 1); k <= j; k++) {
                dp[i][j] = (dp[i][j] + dp[i - 1][k]) % MOD;
            }
        }
    }
    cin >> T;
    for (ll t = 0; t < T; t++) {
        cin >> S;
        ll sm = 0;
        for (auto i : S) {
            sm += i - 'a';
        }
        cout << dp[S.size() - 1][sm] - 1 << endl;
    }
}