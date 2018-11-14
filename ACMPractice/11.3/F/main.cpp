#include <bits/stdc++.h>

using namespace std;

int T;
int F[26];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int t = 0; t < T; t++) {
        int cnt1 = 0, m = 0, cntg1 = 0;
        for (int i = 0; i < 26; i++) {
            cin >> F[i];
            if (F[i] == 1) {
                cnt1++;
            } else if (F[i] != 0) {
                m = (m == 0 ? F[i] : min(m, F[i]));
                cntg1++;
            }
        }
        if (cnt1 == 0) {
            cout << 2 * cntg1 << ' ' << m / 2 << endl;
        } else {
            cout << 2 * cntg1 + 1 << ' ' << (cntg1 == 0 ? cnt1 : min(m / 2, cnt1)) << endl;
        }
    }
}