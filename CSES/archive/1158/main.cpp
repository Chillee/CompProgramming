#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
int N, X;
int dp[MAXN];
int price[MAXN], pages[MAXN];
const int INF = 1e9 + 5;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    fill(dp, dp + MAXN, -INF);
    cin >> N >> X;
    for (int i = 0; i < N; i++)
        cin >> price[i];
    for (int i = 0; i < N; i++)
        cin >> pages[i];
    dp[0] = 0;
    for (int i = 0; i < N; i++) {
        for (int j = X; j >= price[i]; j--) {
            dp[j] = max(dp[j], dp[j - price[i]] + pages[i]);
        }
    }
    int ans = 0;
    for (int i = 0; i <= X; i++) {
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;
}