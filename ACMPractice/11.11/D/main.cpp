#include <bits/stdc++.h>

using namespace std;

const int MAXB = 64;
int K, B;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    K = 5, B = 1;
    for (int k = 2; k < 7; k++) {
        B = k;
        int ans = 0;
        for (int i = K; i < (1 << B); i += K) {
            ans += bitset<MAXB>(i).count();
        }
        cout << ans << endl;
    }
}