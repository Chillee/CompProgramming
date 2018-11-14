#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N;
    double X;
    cin >> N >> X;
    for (int i = 1; i < N; i++) {
        double num = i * X;
        double close = round(num);
        if (abs(close / i - X) <= .0005) {
            cout << close << ' ' << i << endl;
            cout << close / i << endl;
            break;
        }
    }
}