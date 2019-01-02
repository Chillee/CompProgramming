#include <bits/stdc++.h>

using namespace std;

int T;
int A[7];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int t = 0; t < T; t++) {
        int k;
        cin >> k;
        int sm = 0;
        for (int i = 0; i < 7; i++) {
            cin >> A[i];
            sm += A[i];
        }
        int ans = 1e9;
        for (int i = 0; i < 7; i++) {
            int cur = (k % sm == 0) ? 7 * (k / sm - 1) : 7 * (k / sm);
            int cnt = k - (cur / 7) * sm;
            // cout << cnt << ' ' << cur << endl;
            for (int j = 0; j < 7; j++) {
                if (cnt == 0) {
                    ans = min(cur, ans);
                    break;
                }
                cnt -= A[(i + j) % 7];
                cur++;
            }
            if (cnt == 0) {
                ans = min(cur, ans);
            }
        }
        cout << ans << endl;
    }
}