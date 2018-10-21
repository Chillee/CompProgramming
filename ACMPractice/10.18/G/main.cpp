#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

typedef long long ll;
ll T;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (ll t = 0; t < T; t++) {
        vector<ll> nums;
        vector<ll> denoms;
        for (ll i = 0; i < 3; i++) {
            ll a, b;
            char t;
            cin >> a >> t >> b;
            nums.push_back(a);
            denoms.push_back(b);
        }
        ll num = nums[0] * denoms[1] * denoms[2] + nums[1] * denoms[0] * denoms[2] + nums[2] * denoms[0] * denoms[1];
        ll denom = denoms[0] * denoms[1] * denoms[2];
        ll gcd = __gcd(num, denom);
        cout << num / gcd << '/' << denom / gcd << endl;
        // ll gcd = denoms[0];
        // ll prod = 1;
        // for (auto i : denoms) {
        //     gcd = __gcd(i, gcd);
        //     prod *= i;
        // }
        // ll tot = 0;
        // for (ll i = 0; i < 3; i++) {
        //     tot += ((prod / gcd) / denoms[i]) * nums[i];
        // }
        // cout << tot / __gcd(tot, prod / gcd) << '/' << prod / gcd / __gcd(tot, prod / gcd) << endl;
    }
}