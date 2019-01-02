#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 1e5 + 5;
ll N, K;
string A, B;
ll dp[MAXN][3];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;
    cin >> A >> B;
    bool same = true;
    bool differA = false;
    bool differB = false;
    ll cnt = 0, ans = 0;

    for (ll i = 0; i < N; i++) {
        cnt = min(K - (2 - same), cnt * 2);
        cnt += (differA && A[i] == 'a') + (differB && B[i] == 'b');
        if (!same && !differA && A[i] == 'a') {
            differA = true;
            cnt += 1;
        }
        if (!same && !differB && B[i] == 'b') {
            differB = true;
            cnt += 1;
        }
        if (A[i] < B[i] && same) {
            same = false;
        }
        cnt = min(K - (2 - same), cnt);
        ans += min(2ll - same, K);
        ans += max(0ll, cnt);
    }
    cout << ans << endl;
}