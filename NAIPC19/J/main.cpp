#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 1e5 + 5;
const ll MAXT = 105;
const ll INF = 1e8 + 5;
string S, T;
ll dp[MAXN][MAXT];
ll nxt[MAXN][26];
ll lastPos[26];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> S >> T;
    S = '_' + S;
    fill(lastPos, lastPos + 26, INF);
    for (ll i = S.size() - 1; i > 0; i--) {
        for (ll j = 0; j < 26; j++)
            nxt[i][j] = lastPos[j];
        lastPos[S[i] - 'a'] = i;
    }
    for (ll j = 0; j < 26; j++)
        nxt[0][j] = lastPos[j];
    for (ll i = 0; i < S.size(); i++) {
        dp[i][0] = nxt[i][T[T.size() - 1] - 'a'];
    }
    for (ll i = 1; i < T.size(); i++) {
        for (ll j = 0; j < S.size(); j++) {
            ll nxtPos = nxt[j][T[T.size() - i - 1] - 'a'];
            if (nxtPos != INF)
                dp[j][i] = dp[nxtPos][i - 1];
            else
                dp[j][i] = INF;
        }
    }
    ll ans = 0;
    for (ll i = 0; i < S.size(); i++) {
        ans += max(0ll, (ll)S.size() - dp[i][T.size() - 1]);
    }
    cout << ans << endl;
}