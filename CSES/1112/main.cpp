#pragma GCC optimize("O3")
#include <bits/stdc++.h>

#define all(x) x.begin(), x.end()
using namespace std;

typedef long long ll;
const ll MOD = 1e9 + 7;
template <ll MAXN> struct KMP {
    ll pi[MAXN], z[MAXN], n;
    string p;
    void set(string _p) { p = _p, n = p.size(); }
    void computePi() {
        ll j = -1;
        pi[0] = -1;
        for (ll i = 0; i < n; i++) {
            while (j >= 0 && p[i] != p[j])
                j = pi[j];
            j++;
            pi[i + 1] = j;
        }
    }
    void computeZ() {
        for (ll i = 1, l = -1, r = -1; i < n; ++i) {
            z[i] = i >= r ? 0 : min(r - i, z[i - l]);
            while (i + z[i] < n && p[i + z[i]] == p[z[i]])
                z[i]++;
            if (i + z[i] > r)
                l = i, r = i + z[i];
        }
    }
    vector<ll> search(string s) {
        vector<ll> res;
        ll j = 0;
        for (ll i = 0; i < s.size(); i++) {
            while (j >= 0 && s[i] != p[j])
                j = pi[j];
            j++;
            if (j == p.size()) {
                res.push_back(i - n + 1);
                j = pi[j];
            }
        }
        return res;
    }
};
const ll MAXN = 1005;
const ll MAXM = 105;
KMP<MAXN> kmp;
ll N, M;
string S;
ll nxt[MAXN][26];
ll dp[MAXN][MAXM];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    cin >> S;
    M = S.size();
    kmp.set(S);
    kmp.computePi();
    for (ll i = 0; i < S.size(); i++) {
        for (ll nxtC = 0; nxtC < 26; nxtC++) {
            ll cur = i;
            while (cur >= 0 && (nxtC + 'A') != S[cur])
                cur = kmp.pi[cur];
            nxt[i][nxtC] = cur;
        }
    }
    // for (ll i = 0; i < S.size(); i++) {
    //     for (ll j = 0; j < 26; j++) {
    //         cout << nxt[i][j] << ' ';
    //     }
    //     cout << endl;
    // }
    dp[0][0] = 1;
    for (ll i = 0; i <= N; i++) {
        for (ll j = 0; j < M; j++) {
            for (ll c = 0; c < 26; c++) {
                ll z = nxt[j][c];
                if (z != M) {
                    dp[i + 1][z + 1] += dp[i][j];
                    dp[i + 1][z + 1] %= MOD;
                }
            }
        }
    }
    ll ans = 0;
    for (ll i = 0; i < M; i++) {
        ans += dp[N][i];
        ans %= MOD;
    }
    ll total = 1;
    for (ll i = 0; i < N; i++) {
        total *= 26;
        total %= MOD;
    }
    cout << (total - ans + MOD) % MOD << endl;
}