#include <bits/stdc++.h>

using namespace std;

int T;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int t = 0; t < T; t++) {
        int N, X, Y;
        cin >> N >> X >> Y;
        if (X >= (N + 1) / 2 && Y >= N / 2) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}