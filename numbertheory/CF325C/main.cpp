#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll x, y;
vector<ll> ans;
// void sternbrocottree(ll a, ll b, ll c, ll d) {
//     ll mn = a + c, md = b + d;
//     cout << mn << ' ' << md << endl;
//     if (mn == x && md == y) {
//         return;
//     }
//     if (mn * y < md * x) {
//         // cout << "start: " << mn << ' ' << md << endl;
//         ll cnt = 1;
//         // ll mx = 0;
//         // ll cpw = 1;
//         // for (; mx < 60; mx++) {
//         //     if ((mn + cpw * c) * y > 1e18 || (md + cpw * d) * x > 1e18)
//         //         break;
//         //     cpw *= 2;
//         // }
//         // mx++;
//         // cout << "mx: " << mx << endl;
//         // for (ll i = mx; i >= 0; i--) {
//         //     ll pw = 1ll << i;
//         //     if ((mn + pw * c) * y <= (md + pw * d) * x) {
//         //         mn += pw * c;
//         //         md += pw * d;
//         //         cnt += pw;
//         //     }
//         // }
//         ans.push_back(cnt);
//         // cout << mn << ' ' << md << endl;
//         if (mn == x && md == y) {
//             return;
//         }
//         sternbrocottree(mn, md, c, d);
//     } else {
//         // cout << "start: " << mn << ' ' << md << endl;
//         ll cnt = 1;
//         // ll cpw = 1;
//         // ll mx = 0;
//         // for (; mx < 60; mx++) {
//         //     cout << cpw * a << endl;
//         //     if ((mn + cpw * a) * y > 1e18 || (md + cpw * b) * x > 1e18)
//         //         break;
//         //     cpw *= 2;
//         // }
//         // mx++;
//         // // cout << "mx: " << mx << endl;
//         // for (ll i = mx; i >= 0; i--) {
//         //     ll pw = 1ll << i;
//         //     if ((mn + pw * a) * y >= (md + pw * b) * x) {
//         //         mn += pw * a;
//         //         md += pw * b;
//         //         cnt += pw;
//         //     }
//         // }
//         ans.push_back(-cnt);
//         // cout << mn << ' ' << md << endl;
//         if (mn == x && md == y) {
//             return;
//         }
//         sternbrocottree(a, b, mn, md);
//     }
// }
void rec(ll x, ll y) {
    if (x == 1 && y == 1)
        return;
    if (x > y) {
        ll cnt = (x - y + y - 1) / y;
        ans.push_back(cnt);
        rec(x - cnt * y, y);
    } else {
        ll cnt = (y - x + x - 1) / x;
        ans.push_back(-cnt);
        rec(x, y - x * cnt);
    }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> x >> y;
    if (__gcd(x, y) != 1) {
        cout << "Impossible" << endl;
        return 0;
    }
    // sternbrocottree(0, 1, 1, 0);
    rec(x, y);
    // reverse(ans.begin(), ans.end());
    for (ll i = 0; i < ans.size(); i++) {
        // cout << abs(ans[i]) - (i == ans.size() - 1) << (ans[i] < 0 ? "B" : "A");
        cout << abs(ans[i]) << (ans[i] < 0 ? "B" : "A");
    }
    cout << endl;
}