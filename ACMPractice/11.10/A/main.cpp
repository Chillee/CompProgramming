#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXB = 61;
ll T;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (ll t = 0; t < T; t++) {
        ll x, y;
        cin >> x >> y;
        ll curRot = 0;
        for (ll l = MAXB; l > 1; l--) {
            ll mid = 1ll << (l - 1);
            if (x >= mid && y >= mid) {
                x -= mid, y -= mid;
            } else if (x < mid && y < mid) {
                continue;
            } else if (x < mid && y >= mid) {
                x -= mid, y -= mid;
                ll t = -y;
                y = x;
                x = t;
                y += mid, x += mid - 1;
                if (x == mid - 1 && y == mid - 1)
                    break;
                curRot++;
            } else if (x >= mid && y < mid) {
                x -= mid, y -= mid;
                ll t = y;
                y = -x;
                x = t;
                x += mid, y += mid - 1;
                if (x == mid - 1 && y == mid - 1)
                    break;
                curRot--;
            }
        }
        cout << ((curRot % 4) + 4) % 4 << endl;
    }
}