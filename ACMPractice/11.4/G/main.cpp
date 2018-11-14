#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 1e5 + 5;
const ll MOD = 1e9 + 7;
ll N;
ll dp[MAXN][2][2];
ll X[MAXN], Y[MAXN], F[MAXN];
void calc(ll cur) {
    if (cur == -1)
        return;
    calc(X[cur]);
    calc(Y[cur]);
    if (X[cur] == -1 && Y[cur] == -1) {
        for (ll x = 0; x < 2; x++) {
            for (ll y = 0; y < 2; y++) {
                ll corr = !(x && y);
                if (F[cur] == -1) {
                    dp[cur][corr][corr]++;
                } else
                    dp[cur][corr][F[cur]]++;
            }
        }
    } else if (X[cur] != -1 && Y[cur] != -1) {
        for (ll Xa = 0; Xa < 2; Xa++) {
            for (ll Xc = 0; Xc < 2; Xc++) {
                for (ll Ya = 0; Ya < 2; Ya++) {
                    for (ll Yc = 0; Yc < 2; Yc++) {
                        ll corr = !(Xa && Ya);
                        ll act = 0;
                        if (F[cur] == -1) {
                            act = !(Xc && Yc);
                        } else {
                            act = F[cur];
                        }
                        dp[cur][corr][act] += dp[X[cur]][Xa][Xc] * dp[Y[cur]][Ya][Yc];
                        dp[cur][corr][act] %= MOD;
                    }
                }
            }
        }
    } else if (X[cur] != -1 && Y[cur] == -1) {
        for (ll Xa = 0; Xa < 2; Xa++) {
            for (ll Xc = 0; Xc < 2; Xc++) {
                for (ll y = 0; y < 2; y++) {
                    ll corr = !(Xa && y);
                    ll act = 0;
                    if (F[cur] == -1) {
                        act = !(Xc && y);
                    } else {
                        act = F[cur];
                    }
                    dp[cur][corr][act] += dp[X[cur]][Xa][Xc];
                    dp[cur][corr][act] %= MOD;
                }
            }
        }
    }
    // cout << "cur: " << cur + 1 << endl;
    // for (ll i = 0; i < N; i++) {
    //     cout << "#" << i + 1 << ": ";
    //     for (ll j = 0; j < 2; j++)
    //         for (ll k = 0; k < 2; k++)
    //             cout << dp[i][j][k] << " ";
    //     cout << endl;
    // }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (ll i = 0; i < N; i++) {
        cin >> X[i] >> Y[i] >> F[i];
        X[i]--, Y[i]--;
        if (X[i] == -1 && Y[i] != -1) {
            swap(X[i], Y[i]);
        }
    }
    calc(0);
    // for (ll i = 0; i < N; i++) {
    //     cout << "#" << i + 1 << ": ";
    //     for (ll j = 0; j < 2; j++)
    //         for (ll k = 0; k < 2; k++)
    //             cout << dp[i][j][k] << " ";
    //     cout << endl;
    // }
    cout << (dp[0][0][1] + dp[0][1][0]) % MOD << endl;
}