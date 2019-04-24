#include <bits/stdc++.h>

using namespace std;

int N;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    int cur = 0;
    int ans = 0;
    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        cur = max(x, cur);
        if (cur == i + 1) {
            cur = 0;
            ans++;
        }
    }
    cout << ans << endl;
}