#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 3e3 + 5;
ll postFixMin[MAXN];

ll N;
ll S[MAXN], C[MAXN];
int main() {
    cin >> N;
    for (ll i = 0; i < N; i++) {
        cin >> S[i];
    }
    for (ll i = 0; i < N; i++) {
        cin >> C[i];
    }
    for (ll i = 0; i < N; i++) {
        ll mn = 1e9;
        for (ll j = i + 1; j < N; j++) {
            if (S[j] > S[i] && C[j] < mn) {
                mn = C[j];
            }
        }
        postFixMin[i] = mn;
    }
    ll ans = 1e9;
    for (ll i = 0; i < N; i++) {
        for (ll j = i + 1; j < N; j++) {
            if (S[i] < S[j]) {
                ans = min(C[i] + C[j] + postFixMin[j], ans);
            }
        }
    }
    if (ans == 1e9) {
        cout << -1 << endl;
        return 0;
    }
    cout << ans << endl;
}