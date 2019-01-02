#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 1e5 + 5;
ll N, M;
ll X[MAXN], D[MAXN];
ll totSum = 0;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for (ll i = 0; i < M; i++) {
        cin >> X[i] >> D[i];
    }
    for (ll i = 0; i < M; i++) {
        if (D[i] > 0) {
            totSum += (N * (N - 1) / 2) * D[i];
        } else if (D[i] < 0) {
            if (N % 2 == 1) {
                ll mid = N / 2;
                totSum += (2 * mid * (mid + 1) / 2) * D[i];
                // cout << (2 * mid * (mid + 1) / 2) * D[i] << endl;
            } else {
                ll mid = N / 2 - 1;
                totSum += (2 * mid * (mid + 1) / 2) * D[i];
                totSum += (mid + 1) * D[i];
            }
        }
        totSum += N * X[i];
    }
    cout << fixed << setprecision(15) << (long double)totSum / (long double)N << endl;
}