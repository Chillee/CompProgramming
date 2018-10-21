#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

typedef long long ll;
ll T;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (ll t = 0; t < T; t++) {
        ll N, K;
        cin >> N >> K;
        ll num = (2 * K - N * N - N);
        ll denom = 2 * N;
        ll val = (2 * K - N * N - N) / (2 * N);
        if ((num % denom) != 0 || num < 0) {
            cout << "Too drunk to count" << endl;
        } else {
            cout << N + 1 + val << endl;
        }
    }
}