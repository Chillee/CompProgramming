#include <bits/stdc++.h>

using namespace std;

const int MAXN = 55;
int T, N;
int P[MAXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cin >> N;
        for (int i = N; i >= 0; i--) {
            cin >> P[i];
        }
        cout << "Case #" << t << ": ";
        if (P[0] < -1) {
            cout << 0 << endl;
            continue;
        }
        if (P[0] == -1) {
            if (N % 2 == 0) {
                cout << 1 << endl;
                cout << 0 << endl;
                continue;
            } else {
                cout << 0 << endl;
                continue;
            }
        } else {
            if (N % 2 == 0) {
                cout << 0 << endl;
                continue;
            } else {
                cout << 1 << endl;
                cout << 0 << endl;
                continue;
            }
        }
    }
}