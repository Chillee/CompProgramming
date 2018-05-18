#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAXN = 1e5 + 5;
ll N;
ll A[MAXN];
int main() {
    cin >> N;
    for (ll i = 0; i < N; i++) {
        cin >> A[i];
    }
    if (N == 1) {
        cout << 0 << endl;
        return 0;
    }
    vector<ll> initial{A[0], A[0] + 1, A[0] - 1};
    vector<ll> secondary{A[1], A[1] + 1, A[1] - 1};
    vector<ll> results;
    for (auto a : initial) {
        for (auto b : secondary) {
            ll cnt = 0;
            ll diff = b - a;
            ll cur = a;
            bool isPossible = true;
            for (ll i = 0; i < N; i++) {
                if (abs(A[i] - cur) == 0) {
                } else if (abs(A[i] - cur) == 1) {
                    cnt++;
                } else {
                    isPossible = false;
                    break;
                }
                cur += diff;
            }
            if (isPossible) {
                results.push_back(cnt);
            }
        }
    }
    sort(results.begin(), results.end());
    if (results.size() > 0) {

        cout << results[0] << endl;
    } else {
        cout << -1 << endl;
    }
}