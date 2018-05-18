#include <bits/stdc++.h>

using namespace std;

typedef __int128_t ll;

ll N, K, M, D;
int main() {
    cin >> N >> K >> M >> D;
    ll ans = -1;
    for (ll d = 1; d <= D; d++) {
        // ll numDivisors = K * (d - 1LL) + 1LL;
        ll candiesPer = N / K / (d - 1LL);
        if (candiesPer == 0) {
            continue;
        }
        if (candiesPer > M) {
            candiesPer = M;
            if (N / (candiesPer * K) > D) {
                candiesPer = N / (D * K);
                continue;
            }
        }
        // cout << d << ' ' << candiesPer << ' ' << candiesPer * d << endl;
        ans = max(ans, candiesPer * d);
    }
    cout << ans << endl;
    return 0;
}