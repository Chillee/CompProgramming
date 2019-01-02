#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 5005;
const ll MOD = 1e9 + 7;
ll N, A, B, K;
ll dp[MAXN][MAXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> A >> B >> K;
    A--, B--;
    if (A > B) {
        A = N - A - 1;
        B = N - B - 1;
    }
    dp[0][A] = 1;
    for (ll t = 1; t <= K; t++) {
        ll sm = 0;
        ll smLvl = 0;
        for (ll i = 0; i < B; i++) {
            while (smLvl <= (i + B - 1) / 2) {
                sm = (sm + dp[t - 1][smLvl]) % MOD;
                smLvl++;
            }
            dp[t][i] = (sm - dp[t - 1][i] + MOD) % MOD;
        }
    }
    ll ans = 0;
    for (ll i = 0; i < N; i++) {
        ans = (ans + dp[K][i]) % MOD;
    }
    cout << ans << endl;
}