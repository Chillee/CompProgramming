#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2005;
int N;
int X[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> X[i];
    }
    double sum = 0;
    for (int i = 0; i < N; i++) {
        if (X[i] == 0) {
            sum += 2;
        } else {
            sum += 1.0 / X[i];
        }
    }
    cout << fixed << setprecision(20) << sum << endl;
}