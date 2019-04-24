#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll N;
array<ll, 10> add(array<ll, 10> a, array<ll, 10> b) {
    for (ll i = 0; i < 10; i++)
        a[i] += b[i];
    return a;
}
void disp(array<ll, 10> x) {
    for (ll i = 0; i < 10; i++)
        cout << x[i] << ' ';
    cout << endl;
}
array<ll, 10> genCost(ll pow10) {
    array<ll, 10> res = {0};
    for (ll i = 0; i < 10; i++)
        res[i] = ((ll)log10(pow10)) * pow10 / 10;
    return res;
}
array<ll, 10> genFlex(ll x) {
    if (x == 0)
        return {0};
    ll curPow = 1;
    while (curPow * 10 <= x)
        curPow *= 10;
    array<ll, 10> res = {0};
    auto stepDown = genCost(curPow);
    ll i;
    for (i = 1; i * curPow <= x; i++) {
        res = add(res, stepDown);
        res[i - 1] += curPow;
    }
    ll resid = x - (i - 1) * curPow;
    auto nxt = genFlex(resid);
    res = add(res, nxt);
    res[(i - 1)] += resid;
    return res;
}
array<ll, 10> counter(ll x) {
    array<ll, 10> res = {0};
    ll curPow = 1;
    while (curPow <= x) {
        res[0] -= curPow;
        curPow *= 10;
    }
    return res;
}
bool f(ll v) {
    v++;
    auto x = genFlex(v);
    x = add(x, counter(v));
    for (ll i = 0; i < 10; i++) {
        if (x[i] > N)
            return true;
    }
    return false;
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
    cin >> N;
    ll res = binSearch(1, 1e18 + 5);
    cout << res - 1 << endl;
}