#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll A, B, X, Y;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> A >> B >> X >> Y;
    ll xp = X / __gcd(X, Y);
    ll yp = Y / __gcd(X, Y);
    cout << min(B / yp, A / xp) << endl;
}