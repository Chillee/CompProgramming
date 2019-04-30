#pragma GCC optimize("O3")
#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
typedef long long ll;
using namespace std;

const int MAXN=10;
// int dp[MAXN][MAXN];
const int MOD=1e9+7;
typedef vector<ll> Poly;
ll linearRec(Poly S, Poly tr, ll k) {
    int n = S.size();
    auto combine = [&](Poly a, Poly b) {
        Poly res(n * 2 + 1);
        for (int i = 0; i < n + 1; i++)
            for (int j = 0; j < n + 1; j++)
                res[i + j] = (res[i + j] + a[i] * b[j]) % MOD;
        for (int i = 2 * n; i > n; --i)
            for (int j = 0; j < n; j++)
                res[i - 1 - j] = (res[i - 1 - j] + res[i] * tr[j]) % MOD;
        res.resize(n + 1);
        return res;
    };
    Poly pol(n + 1), e(pol);
    pol[0] = e[1] = 1;
    for (++k; k; k /= 2) {
        if (k % 2)
            pol = combine(pol, e);
        e = combine(e, e);
    }
    ll res = 0;
    for (int i = 0; i < n; i++)
        res = (res + pol[i + 1] * S[i]) % MOD;
    return res;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int i=0; i<10; i++) {
        cout<< linearRec({0,3},{7, -10}, i)<<endl;
    }
    // dp[0][0] = 1;
    // for (int r=0; r<MAXN; r++) {
    //     for (int c=0; c<MAXN; c++) {
    //         if (c<r) continue;
    //         if (r==0 && c==0) continue;
    //         else if (c == 0) dp[r][c] = dp[r-1][c];
    //         else if (r==0) dp[r][c] = dp[r][c-1];
    //         else dp[r][c] = dp[r-1][c]+dp[r][c-1];
    //         cout<<r<<' '<<c<<endl;
    //         cout<<dp[r][c]<<endl;
    //     }
    //     cout<<endl;
    // }
    // for (int i=0; i<10; i++) {
    //     cout<<dp[i][i]<<endl;
    // }
}