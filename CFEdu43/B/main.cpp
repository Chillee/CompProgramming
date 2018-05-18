#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll N, M, K;
int main() {
    cin >> N >> M >> K;
    if (K < N) {
        cout << K + 1 << " 1" << endl;
        return 0;
    }
    K -= N;
    M--;
    ll row = N - K / M;
    ll colDiff = K - (K / M) * M;
    if (row % 2) {
        cout << row << ' ' << (M - colDiff) + 1 << endl;
    } else {
        cout << row << ' ' << colDiff + 2 << endl;
    }
}