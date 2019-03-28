#include <bits/stdc++.h>

using namespace std;

int T, R, N;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int i = 0; i < T; i++) {
        cin >> R >> N;
        long double f = M_PI;
        long double s = M_PI / 4;
        s *= pow((long double)1.75, N - 2);
        if (N == 1) {
            cout << fixed << setprecision(20) << f * R * R << endl;
        } else {
            cout << fixed << setprecision(20) << (f + 4 * s) * R * R << endl;
        }
    }
}