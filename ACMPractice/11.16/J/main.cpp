#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll A, B, C, D;
bool isSqrt(ll x) { return (ll)ceil(sqrt(x)) == (ll)floor(sqrt(x)); }
void impossible() {
    cout << "impossible" << endl;
    exit(0);
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> A >> B >> C >> D;
    if (!isSqrt(1 + 8 * A) || !isSqrt(1 + 8 * D)) {
        impossible();
    }
    ll as = sqrt(1 + 8 * A), ds = sqrt(1 + 8 * D);
    if ((1 + as) & 1 || (1 + ds) & 1) {
        impossible();
    }
    ll N = (1 + as) / 2, M = (1 + ds) / 2;
    if (B == 0 && C == 0) {
        if (A == 0 && D == 0) {
            cout << "1" << endl;
            exit(0);
        } else if (A == 0) {
            for (int i = 0; i < M; i++) {
                cout << "1";
            }
            cout << endl;
            return 0;
        } else if (D == 0) {
            for (int i = 0; i < N; i++) {
                cout << "0";
            }
            cout << endl;
            return 0;
        } else {
            impossible();
        }
        return 0;
    }
    if (B + C != N * M) {
        impossible();
    }
    // cout << N << " " << M << endl;
    ll X = (B / M), Y = B - M * X, idx = 0;
    // cout << M - Y << endl;
    for (; idx < X; idx++) {
        cout << "0";
    }
    for (ll i = 0; i < M - Y; i++) {
        cout << "1";
    }
    if (Y > 0) {
        cout << "0";
        idx++;
    }
    for (ll i = M - Y; i < M; i++) {
        cout << "1";
    }
    for (; idx < N; idx++) {
        cout << "0";
    }
    cout << endl;
}