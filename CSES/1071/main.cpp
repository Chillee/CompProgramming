#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T, X, Y;
    cin >> T;
    for (ll t = 0; t < T; t++) {
        cin >> Y >> X;
        X--, Y--;
        ll mx = max(X, Y) + 1;
        ll mxBase = mx * mx;
        bool isLeft = (mx % 2 == 0);
        if (isLeft && Y > X)
            cout << mxBase - X << endl;
        else if (isLeft && Y <= X)
            cout << mxBase - (X + (X - Y)) << endl;
        else if (Y > X)
            cout << mxBase - (Y + (Y - X)) << endl;
        else
            cout << mxBase - Y << endl;
    }
}