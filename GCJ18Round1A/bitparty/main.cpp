#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll MAXC = 1005;
ll T;
ll R, B, C;
ll M[MAXC], S[MAXC], P[MAXC];

ll binsearch(ll l, ll r) {
    if (l == r) {
        return l;
    }
    // cout << l << ' ' << r << endl;
    ll mxTime = (l + r) / 2;
    vector<ll> mxBits;
    for (ll i = 0; i < C; i++) {
        ll mxBitsUsed = max((mxTime - P[i]) / S[i], 0LL);
        // cout << mxBitsUsed << endl;
        mxBits.push_back(min(mxBitsUsed, M[i]));
    }
    // cout << mxTime << endl;
    // cout << "mxBits: ";
    // for (auto i : mxBits) {
    //     cout << i << ' ';
    // }
    // cout << endl;
    sort(mxBits.begin(), mxBits.end(), greater<ll>());
    ll curBits = 0;
    for (ll i = 0; i < R; i++) {
        curBits += mxBits[i];
    }
    if (curBits < B) {
        return binsearch(mxTime + 1, r);
    } else {
        return binsearch(l, mxTime);
    }
}
int main() {
    // freopen("input.txt", "r", stdin);
    cin >> T;
    for (ll t = 0; t < T; t++) {
        cin >> R >> B >> C;
        for (ll i = 0; i < C; i++) {
            cin >> M[i] >> S[i] >> P[i];
        }
        cout << "Case #" << t + 1 << ": " << binsearch(0, 2e18) << endl;
    }
}