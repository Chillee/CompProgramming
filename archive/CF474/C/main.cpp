#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll X, D;
vector<ll> res;
int main() {
    cin >> X >> D;
    ll cur = 1;
    while (X > 0) {
        ll mxPow = 1;
        while ((1 << mxPow) - 1 <= X) {
            mxPow++;
        }
        mxPow--;
        for (ll i = 0; i < mxPow; i++) {
            res.push_back(cur);
            if (res.size() > 1e4) {
                cout << -1 << endl;
                return 0;
            }
        }
        cur += D;
        X -= (1 << mxPow) - 1;
    }
    cout << res.size() << endl;
    for (auto i : res) {
        cout << i << ' ';
    }
    cout << endl;
}