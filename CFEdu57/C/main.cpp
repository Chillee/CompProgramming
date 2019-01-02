#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll T;
map<ll, ll> ans;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (ll i = 3; i <= 360; i++) {
        for (ll j = 0; j < i - 2; j++) {
            if (((i - 2) * 180 - j * 180) % i != 0)
                continue;
            ll cur = (i - 2) * 180 / i - j * 180 / i;
            if (ans.find(cur) == ans.end()) {
                ans[cur] = i;
            }
        }
    }
    // for (ll i = 3; i <= 360; i++) {
    //     if (360 % (2 * i) == 0) {
    //         angles[i] = 360 / (2 * i);
    //     }
    // }
    // ans[179] = 360;
    cin >> T;
    for (ll i = 0; i < T; i++) {
        ll ang;
        cin >> ang;
        if (ans.find(ang) == ans.end()) {
            cout << -1 << endl;
        } else
            cout << ans[ang] << endl;
        // for (auto j : angles) {
        //     // cout << (j.first - 2) * 180 / j.first << endl;
        //     if (ang % j.second == 0 && ang <= (j.first - 2) * 180 / j.first) {
        //         cout << j.first << endl;
        //         found = true;
        //         break;
        //     }
        // }
    }
}