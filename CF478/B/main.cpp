#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll N;
ll A[20];
int main() {
    ll sum = 0;
    N = 14;
    for (ll i = 0; i < N; i++) {
        cin >> A[i];
    }
    ll res = 0;
    for (ll i = 0; i < N; i++) {
        ll cur[20];
        for (ll t = 0; t < N; t++) {
            cur[t] = A[t];
        }
        ll count = cur[i];
        if (count == 0) {
            continue;
        }
        cur[i] = 0;
        for (ll j = 0; j < N; j++) {
            cur[j] += count / N;
        }
        count = count % N;
        for (ll j = 1; j <= count; j++) {
            cur[(i + j) % N]++;
        }
        // for (ll j = 0; j < N; j++) {
        //     cout << cur[j] << " ";
        // }
        // cout << endl;
        ll sm = 0;
        for (ll j = 0; j < N; j++) {
            if (cur[j] % 2 == 0) {
                sm += cur[j];
            }
        }
        res = max(res, sm);
    }
    cout << res << endl;
}