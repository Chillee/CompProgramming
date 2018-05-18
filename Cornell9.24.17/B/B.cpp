#include <bits/stdc++.h>

using namespace std;

int N;
int main() {
    cin >> N;
    int cusum = 0;
    int mn = 1e9;
    int mx = -1e9;
    for (int i = 0; i < N; i++) {
        int a, b;
        cin >> a >> b;
        if (b == 1) {
            mn = min(mn, cusum);
        } else {
            mx = max(mx, cusum);
        }
        cusum += a;
    }
    if (mn <= mx) {
        cout << "Impossible" << endl;
        return 0;
    }
    if (mx == -1e9) {
        cout << "Infinity" << endl;
        return 0;
    }
    cout << 1899 - (mx - cusum) << endl;
}