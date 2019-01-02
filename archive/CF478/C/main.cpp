#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAXN = 2e5;
ll N, Q;
ll A[MAXN];
ll prefSum[MAXN];
ll binsearch(ll l, ll r, ll val) {
    ll mid = (l + r) / 2;
    if (l == r - 1) {
        if (prefSum[r] <= val) {
            return r;
        }
        return l;
    }
    // cout << l << ' ' << r << ' ' << val << endl;
    if (prefSum[mid] <= val) {
        return binsearch(mid, r, val);
    } else {
        return binsearch(l, mid, val);
    }
}
int main() {
    cin >> N >> Q;
    for (ll i = 0; i < N; i++) {
        cin >> A[i];
    }
    prefSum[0] = 0;
    for (ll i = 1; i <= N; i++) {
        prefSum[i] = prefSum[i - 1] + A[i - 1];
    }

    ll cur = 0;
    for (ll i = 0; i < Q; i++) {
        ll k;
        cin >> k;
        cur += k;
        ll res = binsearch(0, N, cur);
        if (res >= N) {
            cur = 0;
        }
        if (res != N) {
            cout << N - res << endl;
        } else {
            cout << N << endl;
        }
    }
}