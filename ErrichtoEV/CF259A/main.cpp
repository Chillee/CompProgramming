#include <bits/stdc++.h>

using namespace std;

typedef long double ll;
ll M;
int N;
ll binExp(ll base, int exp) {
    if (exp == 0)
        return 1;
    return binExp(base * base, exp / 2) * (exp % 2 == 1 ? base : 1);
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> M >> N;
    double ans = 0;
    for (int i = 1; i <= M; i++) {
        ans += i * (binExp(i / M, N) - binExp((i - 1) / M, N));
    }
    cout << fixed << setprecision(20) << ans << endl;
}