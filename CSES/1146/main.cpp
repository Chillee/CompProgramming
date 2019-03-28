#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll binExp(ll base, ll exp) {
    if (exp == 0)
        return 1;
    return binExp(base * base, exp / 2) * (exp % 2 == 1 ? base : 1);
}
ll N;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll ans = 0;
    cin >> N;
    N++;
    ll cnt = 0;
    for (ll b = 60; b >= 0; b--) {
        if (N & (1ll << b)) {
            ans += b * binExp(2, b - 1);
            ans += cnt * (1ll << b);
            cnt++;
        }
    }
    cout << ans << endl;
}