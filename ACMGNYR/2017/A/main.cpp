#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

int P, K, N;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> P;
    for (int t = 0; t < P; t++) {
        cin >> K >> N;
        cout << K << ' ' << N * (N + 1) / 2 + N << endl;
    }
}