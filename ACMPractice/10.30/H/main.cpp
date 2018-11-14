#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll N, M, X1, X2, Y1, Y2;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M >> X1 >> Y1 >> X2 >> Y2;
    ll cnt = 0;
    if (M % 2) {
        cnt += (N - (X2 - X1 + 1));
    }
    if ((Y1 - 1) % 2) {
        cnt += X2 - X1 + 1;
    }
    if ((M - Y2) % 2) {
        cnt += X2 - X1 + 1;
    }
    cout << (cnt + 1) / 2 << endl;
}