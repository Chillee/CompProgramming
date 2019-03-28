#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 2e5 + 5;
const ll INF = 1e18 + 5;
ll N;
ll A[MAXN];
template <typename T> struct Seg {
    const ll N;
    vector<T> seg;
    T unit;
    const function<T(T, T)> combine;
    Seg(ll n, T arr[], T u, function<T(T, T)> cF) : N(n), unit(u), combine(cF), seg(N * 2) {
        for (ll i = 0; i < N; i++)
            seg[i + N] = arr[i];
        build();
    }
    void build() {
        for (ll i = N - 1; i > 0; --i)
            seg[i] = combine(seg[i << 1], seg[i << 1 | 1]);
    }

    void modify(ll p, T value) {
        for (seg[p += N] = value; p >>= 1;)
            seg[p] = combine(seg[p << 1], seg[p << 1 | 1]);
    }

    T query(ll l, ll r) {
        T resl = unit;
        T resr = unit;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                resl = combine(resl, seg[l++]);
            if (r & 1)
                resr = combine(seg[--r], resr);
        }
        return combine(resl, resr);
    }
};
Seg<ll> *mn, *mx;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (ll i = 0; i < 2 * N; i++) {
        cin >> A[i];
    }
    sort(A, A + 2 * N);
    mn = new Seg<ll>(2 * N, A, INF, [](auto a, auto b) { return min(a, b); });
    mx = new Seg<ll>(2 * N, A, -INF, [](auto a, auto b) { return max(a, b); });
    ll ans = INF;
    for (ll i = 0; i < N; i++) {
        ll a = mx->query(i, i + N) - mn->query(i, i + N);
        ll b = max(mx->query(0, i), mx->query(i + N, 2 * N)) - min(mn->query(0, i), mn->query(i + N, 2 * N));
        ans = min(ans, a * b);
    }
    cout << ans << endl;
}