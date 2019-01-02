#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll T, L, R;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (ll t = 0; t < T; t++) {
        cin >> L >> R;
        cout << L << " " << 2 * L << endl;
    }
}