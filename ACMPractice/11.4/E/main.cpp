#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 1e3 + 5;
ll MOD;
string S;
ll binExp(ll base, ll exp) {
    if (exp == 0)
        return 1;
    return binExp(base * base % MOD, exp / 2) * (exp % 2 == 1 ? base : 1) % MOD;
}
ll pow10[MAXN];
bool dp[MAXN][MAXN];
array<ll, 2> prv[MAXN][MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> S >> MOD;
    for (ll i = 0; i < MAXN; i++) {
        pow10[i] = binExp(10, i);
    }
    reverse(S.begin(), S.end());
    ll start = 0;
    for (ll i = 0; i < S.size(); i++) {
        if (S[i] == '?' && i == S.size() - 1) {
            start += pow10[i] * 1;
            start %= MOD;
        } else if (S[i] == '?') {
            continue;
        } else {
            start += (S[i] - '0') * pow10[i];
            start %= MOD;
        }
    }
    dp[0][start] = true;
    prv[0][start] = {-1, -1};
    array<ll, 2> res;
    for (ll i = 0; i < S.size(); i++) {
        if (S[i] != '?') {
            for (ll j = 0; j < MOD; j++) {
                dp[i + 1][j] = dp[i][j];
                prv[i + 1][j] = {j, S[i] - '0'};
            }
        } else {
            for (ll k = 0; k <= 9; k++) {
                for (ll j = 0; j < MOD; j++) {
                    if (dp[i][j]) {
                        ll nxt = 0;
                        if (i == S.size() - 1) {
                            if (k == 0)
                                continue;
                            nxt = (j + (k - 1) * pow10[i]) % MOD;
                        } else {
                            nxt = (j + k * pow10[i]) % MOD;
                        }
                        if (dp[i + 1][nxt])
                            continue;
                        dp[i + 1][nxt] = true;
                        prv[i + 1][nxt] = {j, k};
                        if (nxt == 0) {
                            auto cur = prv[i + 1][nxt];
                            for (ll l = i; l >= 0; l--) {
                                S[l] = cur[1] + '0';
                                cur = prv[l][cur[0]];
                            }
                            reverse(S.begin(), S.end());
                            if (S[0] == '?') {
                                S[0] = '1';
                            }
                            for (auto &i : S) {
                                if (i == '?') {
                                    i = '0';
                                }
                            }
                            cout << S << endl;
                            exit(0);
                        }
                    }
                }
            }
        }
    }
    cout << "*" << endl;
}