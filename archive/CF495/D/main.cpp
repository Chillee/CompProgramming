#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 5;
int T;
int counts[MAXN];
int mxEl;
int firstFailed;
bool test(int w, int h, int zx, int zy) {
    int curCounts[MAXN] = {0};
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            curCounts[abs(i - zx) + abs(j - zy)]++;
        }
    }
    for (int i = 0; i < MAXN; i++) {
        if (curCounts[i] != counts[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int i = 0; i < T; i++) {
        int t;
        cin >> t;
        counts[t]++;
        mxEl = max(t, mxEl);
    }
    for (int i = 1; i < MAXN; i++) {
        if (counts[i] % 4 != 0 || counts[i] == 0) {
            firstFailed = i;
            break;
        }
    }
    for (int i = 1; i * i <= T; i++) {
        if (T % i == 0) {
            for (int x = 0; x <= i / 2; x++) {
                for (int y = 0; y <= (T / i) / 2; y++) {
                    if (abs(i - 1 - x) + abs(T / i - 1 - y) != mxEl) {
                        continue;
                    }
                    if (x != firstFailed - 1 && y != firstFailed - 1) {
                        continue;
                    }
                    if (test(i, T / i, x, y)) {
                        cout << i << ' ' << T / i << endl;
                        cout << x + 1 << ' ' << y + 1 << endl;
                        exit(0);
                    }
                }
            }
        }
    }
    cout << -1 << endl;
}