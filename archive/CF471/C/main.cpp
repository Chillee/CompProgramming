#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll Q;
ll L, R;
set<ll> vals;
set<ll> sqrts;

ll bin_exp(ll base, ll exp) {
    if (exp == 0)
        return 1;
    return bin_exp(base * base, exp / 2) * (exp % 2 == 1 ? base : 1);
}

ll bin_search(ll val, ll l, ll r, vector<ll> &arr) {
    if (l == r - 1) {
        return l;
    }
    ll mid = (l + r) / 2;
    if (val < arr[mid]) {
        return bin_search(val, l, mid, arr);
    } else {
        return bin_search(val, mid, r, arr);
    }
}

int main() {
    vals.insert(1);
    sqrts.insert(1);
    vals.insert(2e18);
    sqrts.insert(2e18);
    for (ll cur = 2; cur <= (ll)1e6; cur++) {
        for (ll i = 3; i <= 60; i++) {
            ll t = bin_exp(cur, i);
            vals.insert(t);
            if (((ll)sqrtl((long double)t)) * ((ll)sqrtl((long double)t)) == t) {
                sqrts.insert(t);
            }
            if ((long double)t > (long double)(1e18 + 1) / (long double)cur) {
                break;
            }
        }
    }
    vector<ll> vvals(vals.begin(), vals.end());
    vector<ll> vsqrts(sqrts.begin(), sqrts.end());
    cin >> Q;
    for (ll i = 0; i < Q; i++) {
        cin >> L >> R;
        ll res = 0;
        long double lower = sqrtl((long double)L);
        long double upper = sqrtl((long double)R);
        res += floor(upper) - ceil(lower) + 1;
        ll uidx = bin_search(R, 0, vsqrts.size(), vsqrts);
        ll lidx = bin_search(L, 0, vsqrts.size(), vsqrts);
        res -= uidx - lidx;

        uidx = bin_search(R, 0, vvals.size(), vvals);
        lidx = bin_search(L, 0, vvals.size(), vvals);
        res += uidx - lidx;
        cout << res << endl;
    }
}