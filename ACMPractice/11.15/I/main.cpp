#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N, T;
    int H[10];
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> H[i];
    }
    cin >> T;
    int best = -1, bestIdx = -1;
    for (int i = 0; i < N; i++) {
        int x = H[i] * (T / H[i]);
        if (x > best) {
            best = x;
            bestIdx = i;
        }
    }
    cout << H[bestIdx] << endl;
}