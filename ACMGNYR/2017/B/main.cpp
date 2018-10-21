#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll P;
ll K, B, N;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> P;
    for (ll t = 0; t < P; t++) {
        cin >> K >> B >> N;
        ll origB = B;
        ll ans = 0;
        while (N > 0) {
            // cout << N << ' ' << B << endl;
            ans += (N % B) * (N % B);
            N -= N % B;
            N /= B;
        }
        cout << K << ' ' << ans << endl;
    }
}