#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MOD = 998244353;
ll N;
string S;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> S;
    char f = S[0];
    char l = S[S.size() - 1];
    ll fcnt = 1, lcnt = 1;
    for (ll i = 0; i < S.size(); i++) {
        if (S[i] != f)
            break;
        fcnt++;
    }

    for (ll i = S.size() - 1; i >= 0; i--) {
        if (S[i] != l)
            break;
        lcnt++;
    }
    if (f != l) {
        cout << (lcnt + fcnt - 1) % MOD << endl;
    } else {
        cout << (fcnt * lcnt) % MOD << endl;
    }
}