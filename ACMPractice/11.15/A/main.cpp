#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;
int N;
int H[MAXN], R[MAXN], T[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    int mx = 0;
    for (int i = 0; i < N; i++) {
        cin >> H[i] >> R[i] >> T[i];
        mx = max(mx, H[i]);
    }
    for (int i = 0; i < mx * 1865; i++) {
        bool valid = true;
        for (int j = 0; j < N; j++) {
            // cout << i << ' ' << j << endl;
            int hour = i % H[j];
            if (R[j] > T[j]) {
                if (hour > R[j] || hour < T[j])
                    valid = false;
                else
                    continue;
            } else {
                if (hour > R[j] && hour < T[j])
                    valid = false;
                else
                    continue;
            }
        }
        if (valid) {
            cout << i << endl;
            return 0;
        }
    }
    cout << "impossible" << endl;
}