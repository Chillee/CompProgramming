#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 2e5 + 5;
const ll INF = 1e9 + 5;
ll MOD;
ll pow10[MAXN];
string s;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> s;
    reverse(s.begin(), s.end());
    cin >> MOD;
    pow10[0] = 1;
    for (ll i = 1; i < MAXN; i++) {
        pow10[i] = (pow10[i - 1] * 10) % MOD;
    }
    ll cur = 0;
    for (ll i = 0; i < s.size(); i++) {
        cur = (cur + (s[i] - '0') * pow10[i]) % MOD;
    }
    ll ans = cur;
    for (ll i = s.size() - 1; i > 0; i--) {
        cur -= pow10[s.size() - 1] * (s[i] - '0');
        cur = ((cur % MOD) + MOD) % MOD;
        cur *= 10;
        cur += s[i] - '0';
        cur %= MOD;
        if (s[i - 1] != '0') {
            ans = min(ans, cur);
        }
    }
    cout << ans << endl;
}