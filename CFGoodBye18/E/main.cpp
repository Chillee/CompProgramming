#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 5e5 + 500;
ll N;
ll degrees[MAXN];
struct seg {
    ll N;
    ll seg[2 * MAXN];
    void build() {
        for (ll i = N - 1; i >= 0; i--)
            seg[i] = seg[i << 1] + seg[i << 1 | 1];
    }

    void modify(ll p, ll val) {
        for (seg[p += N] = val; p > 0; p >>= 1)
            seg[p >> 1] = seg[p] + seg[p ^ 1];
    }

    ll query(ll l, ll r) {
        ll res = 0;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                res += seg[l++];
            if (r & 1)
                res += seg[--r];
        }
        return res;
    }
};
struct segM {
    ll N;
    ll seg[2 * MAXN];
    void build() {
        for (ll i = N - 1; i >= 0; i--)
            seg[i] = min(seg[i << 1], seg[i << 1 | 1]);
    }

    void modify(ll p, ll val) {
        for (seg[p += N] = val; p > 0; p >>= 1)
            seg[p >> 1] = min(seg[p], seg[p ^ 1]);
    }

    ll query(ll l, ll r) {
        ll res = 1e9 + 5;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                res = min(res, seg[l++]);
            if (r & 1)
                res = min(res, seg[--r]);
        }
        return res;
    }
};
struct segMx {
    ll N;
    ll seg[2 * MAXN];
    void build() {
        for (ll i = N - 1; i >= 0; i--)
            seg[i] = max(seg[i << 1], seg[i << 1 | 1]);
    }

    void modify(ll p, ll val) {
        for (seg[p += N] = val; p > 0; p >>= 1)
            seg[p >> 1] = max(seg[p], seg[p ^ 1]);
    }

    ll query(ll l, ll r) {
        ll res = -1e9 + 5;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                res = max(res, seg[l++]);
            if (r & 1)
                res = max(res, seg[--r]);
        }
        return res;
    }
};

using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

struct chash {
    const ll RANDOM = (long long)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
    static unsigned long long hash_f(unsigned long long x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    static unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }
    ll operator()(ll x) const { return hash_f(x); }
};
gp_hash_table<ll, null_type, chash> res;

ll pre[MAXN], suff[MAXN];
seg sm;
segM suffMn;
segMx preMx;
ll findIdx(ll v) {
    auto res = lower_bound(degrees, degrees + N + 1, v, [](ll a, ll b) { return a > b; }) - degrees;
    return res;
}
ll sumMin(ll l, ll v) {
    ll idx = findIdx(v);
    if (idx <= l)
        return sm.query(l, sm.N);

    ll val = (idx - l) * (v) + sm.query(idx, sm.N);
    return val;
}
bool impossible[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    sm.N = N + 1;
    suffMn.N = N + 1;
    fill(begin(suffMn.seg), end(suffMn.seg), 1e9);
    fill(begin(preMx.seg), end(preMx.seg), -1e9);
    preMx.N = N + 1;
    for (ll i = 1; i <= N; i++)
        cin >> degrees[i];
    sort(degrees + 1, degrees + N + 1, greater<ll>());
    degrees[0] = N + 1;
    for (ll i = 1; i <= N; i++) {
        sm.seg[i + sm.N] = degrees[i];
    }
    sm.build();
    ll totSum = sm.query(0, sm.N);
    for (ll k = 1; k <= N; k++) {
        ll val = -sm.query(1, k + 1) + k * (k + 1);
        val += sumMin(k + 1, k + 1);
        suff[k] = val;
        suffMn.seg[k + suffMn.N] = val;
    }
    suffMn.build();

    for (ll k = 1; k <= N; k++) {
        ll val = sm.query(1, k + 1) - k * (k - 1);
        val -= sumMin(k + 1, k);
        pre[k] = val;
        preMx.seg[k + preMx.N] = val;
    }
    preMx.build();
    for (ll i = 1; i <= N; i++) {
        // cout << preMx.query(1, i + 1) << endl;
        if (preMx.query(1, i + 1) > i) {
            impossible[i] = true;
        }
    }
    for (ll j = 1; j <= N; j++) {
        ll r = degrees[j - 1], l = degrees[j];
        if (degrees[j - 1] == degrees[j] || impossible[j - 1])
            continue;
        ll val = j * (j - 1) - sm.query(1, j) + sumMin(j, j);
        r = min(r, val);
        r = min(r, suffMn.query(j, suffMn.N));
        l = max(l, preMx.query(1, j));
        for (ll i = l; i <= r; i++) {
            if ((i + totSum) % 2 == 0) {
                res.insert(i);
            }
        }
    }
    ll l = 0, r = degrees[N];
    if (degrees[N] == 0 || impossible[N]) {
    } else {
        ll val = N * (N + 1) - sm.query(1, sm.N);
        r = min(r, val);
        l = max(l, preMx.query(1, preMx.N));
        for (ll i = l; i <= r; i++) {
            if ((i + totSum) % 2 == 0) {
                res.insert(i);
            }
        }
    }
    vector<ll> finalRes;
    for (auto i : res)
        finalRes.push_back(i);
    sort(finalRes.begin(), finalRes.end());

    if (finalRes.size() == 0) {
        cout << -1 << endl;
        return 0;
    }
    for (auto i : finalRes) {
        cout << i << ' ';
    }
    cout << endl;
}