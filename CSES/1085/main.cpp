#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 5e5 + 5;
ll N, K;
ll A[MAXN];
bool f(ll mxV) {
    ll cnt = 1;
    ll cur = 0;
    for (ll i = 0; i < N; i++) {
        if (cur + A[i] > mxV)
            cnt++, cur = 0;
        cur += A[i];
        if (cur > mxV)
            return false;
    }
    return cnt <= K;
}
ll binSearch(ll l, ll r) {
    ll mid = (l + r) / 2;
    if (l == r)
        return l;
    if (f(mid))
        return binSearch(l, mid);
    else
        return binSearch(mid + 1, r);
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;
    for (ll i = 0; i < N; i++)
        cin >> A[i];
    cout << binSearch(0, 1e18) << endl;
}