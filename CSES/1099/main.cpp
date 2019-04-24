#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;

int T, N;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin >> N;
        int ans = 0;
        for (int i = 0; i < N; i++) {
            int x;
            cin >> x;
            if (i % 2 == 1)
                ans ^= x;
        }
        cout << (ans == 0 ? "second" : "first") << endl;
    }
}