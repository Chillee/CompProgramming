#include <bits/stdc++.h>

using namespace std;

int T, N;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int t = 0; t < T; t++) {
        int N;
        cin >> N;
        int cur = 0;
        for (int i = 0; i < N; i++) {
            int x;
            cin >> x;
            cur ^= (x % 4);
        }
        cout << (cur == 0 ? "second" : "first") << endl;
    }
}