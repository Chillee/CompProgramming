#include <bits/stdc++.h>

using namespace std;

int T;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int t = 0; t < T; t++) {
        int N;
        cin >> N;
        int cur = 1;
        for (int i = 1; i <= N; i++) {
            cur = (cur * i) % 10;
        }
        cout << cur << endl;
    }
}