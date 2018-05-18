#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAXN = 2e5 + 5;
ll N, K;
vector<ll> A;

int main() {
    cin >> N >> K;
    for (ll i = 0; i < N; i++) {
        ll t;
        cin >> t;
        A.push_back(t);
    }
    sort(A.begin(), A.end());

    if (K == 0 && A[0] == 1) {
        cout << -1 << endl;
    } else if (K == 0) {
        cout << 1 << endl;
    } else if (K < N && A[K - 1] == A[K]) {
        cout << -1 << endl;
    } else {
        cout << A[K - 1] << endl;
    }
}