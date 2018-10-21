#include <bits/stdc++.h>

#define endl '\n';
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
            int p;
            cin >> p;
            ans += (p != 0);
        }
        cout << ans << endl;
    }
}