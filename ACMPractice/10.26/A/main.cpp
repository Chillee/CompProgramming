#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

typedef long long ll;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll G, S;
    cin >> S >> G;
    if (S % G != 0 || S == G) {
        cout << -1 << endl;
        return 0;
    }
    cout << G << ' ' << S - G << endl;
}