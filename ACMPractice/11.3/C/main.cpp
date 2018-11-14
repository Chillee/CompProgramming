#include <bits/stdc++.h>

using namespace std;

#define endl '\n';
typedef long double ld;
int T;
long long A, B, C, X;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin >> A >> B >> C >> X;
        ld dist1 = sqrt(pow(2 * C + B, 2) + pow(A, 2));
        ld dist2 = (X / 100.0) * sqrt(pow(A, 2) + pow(B, 2));
        ld u = (X / 100.0) * B;
        ld v = (X / 100.0) * A;
        ld dist3 = sqrt(pow(2 * C + B - u, 2) + pow(A - v, 2));
        cout << fixed << setprecision(20) << dist1 + dist2 + dist3 << endl;
    }
}