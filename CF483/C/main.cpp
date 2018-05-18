#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll MOD = 1e18 + 9;
ll N, P, Q, B;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (ll i = 0; i < N; i++) {
        cin >> P >> Q >> B;
        ll gcd = __gcd(Q, P);
        ll orig = B;
        Q = Q / gcd;
        P = P / gcd;
        while (Q > 1) {
            gcd = __gcd(B, Q);
            if (gcd == 1) {
                break;
            }
            Q /= gcd;
        }
        if (Q == 1) {
            cout << "Finite" << endl;
        } else {
            cout << "Infinite" << endl;
        }
    }
}