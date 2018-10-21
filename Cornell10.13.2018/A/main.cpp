#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

typedef long long ll;
const ll MAXN = 5e5 + 5;
ll N;
ll A[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    ll numPos = 0, numNeg = 0;
    ll ans = 0;
    ll minAbs = 1e9 + 5;
    for (ll i = 0; i < N; i++) {
        cin >> A[i];
        ans += abs(A[i]);
        if (A[i] > 0)
            numPos++;
        else if (A[i] < 0)
            numNeg++;
        minAbs = min(minAbs, abs(A[i]));
    }
    if (N == 1) {
        cout << A[0] << endl;
        return 0;
    }
    if (numPos != N && numNeg != N) {
        cout << ans << endl;
    } else {
        cout << ans - 2 * minAbs << endl;
    }
}