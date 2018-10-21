#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

int T;
int A, B, D;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int i = 0; i < T; i++) {
        cin >> A >> B >> D;
        double ans = (1.0 / 2.0) * D * D;
        cout << fixed << setprecision(20) << ans << endl;
    }
}