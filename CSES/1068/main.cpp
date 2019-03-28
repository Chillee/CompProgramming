#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    long long N;
    cin >> N;
    while (N != 1) {
        cout << N << ' ';
        if (N & 1)
            N = N * 3 + 1;
        else
            N /= 2;
    }
    cout << 1 << endl;
}