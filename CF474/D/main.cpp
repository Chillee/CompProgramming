#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAXN = 100;
ll Q;
ll shifts[MAXN];
ll getLayer(ll x) {
    ll res = 0;
    while (x != 0) {
        x >>= 1;
        res++;
    }
    return res - 1;
}
ll norm(ll x, ll mod) { return ((x % mod) + mod) % mod; }
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> Q;
    for (ll q = 0; q < Q; q++) {
        ll type, x, k;
        cin >> type;
        if (type == 1) {
            cin >> x >> k;
            ll layer = getLayer(x);
            ll mod = 1LL << layer;
            shifts[layer] = norm(shifts[layer] - 2 * k, 2 * mod);
            shifts[layer - 1] = norm(shifts[layer - 1] + k, 2 * mod);
            // cout << "shifts: " << shifts[layer] << endl;
        } else if (type == 2) {
            cin >> x >> k;
            ll layer = getLayer(x);
            ll mod = 1LL << layer;
            if (layer == 0) {
                continue;
            }
            shifts[layer - 1] = norm(shifts[layer - 1] + k, 2 * mod);
        } else if (type == 3) {
            cin >> x;
            while (x != 1) {
                ll layer = getLayer(x);
                ll mod = 1LL << layer;
                cout << x << ' ';
                x = (((x - mod + shifts[layer - 1]) % mod) + mod) / 2;
            }
            cout << 1;
            cout << endl;
        }
    }
}