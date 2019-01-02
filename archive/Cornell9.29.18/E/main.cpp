#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

typedef long long ll;
ll N, M;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    ll cur = 0;
    ll ans = 0;
    for (ll i = 0; i < M; i++) {
        ll t;
        cin >> t;
        t--;
        if (t >= cur) {
            ans += t - cur;
        } else {
            ans += (t + N) - cur;
        }
        cur = t;
    }
    cout << ans << endl;
}