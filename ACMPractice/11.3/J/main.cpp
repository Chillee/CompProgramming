#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
typedef long long ll;
ll T;
ll N;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin >> N;
        ll cnt = bitset<60>(N).count();
        cout << (N + 1) - (1LL << cnt) << endl;
    }
}