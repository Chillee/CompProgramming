#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 2e5 + 5;
ll N;
array<ll, 3> jobs[MAXN];
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

struct chash {
    static unsigned long long hash_f(unsigned long long x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    static unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }
    ll operator()(ll x) const { return hash_f(x); }
};
struct Seg {
    ll N;
    ll seg[4 * MAXN];
    ll get(ll x) { return seg[x]; }
    void modify(ll p, ll val) {
        p += N;
        for (seg[p] = max(seg[p], val); p > 0; p >>= 1) {
            seg[p >> 1] = max(get(p), get(p ^ 1));
        }
    }

    ll query(ll l, ll r) {
        ll res = 0;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                res = max(res, get(l++));
            if (r & 1)
                res = max(res, get(--r));
        }
        return res;
    }
} seg;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (ll i = 0; i < N; i++)
        cin >> jobs[i][0] >> jobs[i][1] >> jobs[i][2];
    sort(jobs, jobs + N, [](array<ll, 3> a, array<ll, 3> b) { return a[1] < b[1]; });
    map<int, int> comp;
    for (int i = 0; i < N; i++)
        comp[jobs[i][0]], comp[jobs[i][1]];
    int idx = 0;
    for (auto &i : comp)
        i.second = idx++;
    for (int i = 0; i < N; i++) {
        jobs[i][0] = comp[jobs[i][0]];
        jobs[i][1] = comp[jobs[i][1]];
    }
    seg.N = 2 * N;
    ll ans = 0;
    for (ll i = 0; i < N; i++) {
        ll cur = seg.query(0, jobs[i][0]) + jobs[i][2];
        ans = max(ans, cur);
        seg.modify(jobs[i][1], cur);
    }
    cout << ans << endl;
}