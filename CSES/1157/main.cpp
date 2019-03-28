#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll R, C;
ll mxPow2(ll x) {
    ll pw = 0;
    ll cur = 1;
    while (cur <= x)
        pw++, cur *= 2;
    return pw;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int R, C;
    ll offset = 0;
    cin >> R >> C;
    R--, C--;
    while (R != 0 || C != 0) {
        // cout << R << ' ' << C << ' ' << mxPow2(R) << ' ' << mxPow2(C) << endl;
        if (R < C)
            swap(R, C);
        if (mxPow2(R) == mxPow2(C)) {
            R -= (1 << (mxPow2(R) - 1)), C -= (1 << (mxPow2(C) - 1));
            continue;
        }
        offset += 1 << (mxPow2(R) - 1);
        R %= (1 << (mxPow2(R) - 1));
    }
    cout << offset << endl;
    // cout << R << ' ' << C << endl;
    // while (mxPow2(R) > mxPow2(C))
}