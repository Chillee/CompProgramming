#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MAXN = 1e5 + 5;
const ll INF = 1e6 + 5;
struct Seg {
    ll l;
    ll r;
    ll col;
    inline bool operator<(Seg x) const {
        if (l != x.l)
            return l < x.l;
        return r < x.r;
    }
};
ll L, C, N;
ll numColor[MAXN];
set<Seg> cur;
void add(Seg seg) {
    if (seg.l > seg.r)
        return;
    numColor[seg.col] += (seg.r - seg.l) + 1;
    cur.insert(seg);
}
auto erase(set<Seg>::iterator seg) {
    numColor[seg->col] -= seg->r - seg->l + 1;
    return cur.erase(seg);
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> L >> C >> N;
    numColor[0] = L;
    cur.insert({0, L - 1, 0});
    for (ll i = 0; i < N; i++) {
        ll P, X, A, B;
        cin >> P >> X >> A >> B;
        P--, X--;
        ll S = numColor[P];
        ll M1 = (A + S * S) % L;
        ll M2 = (A + (S + B) * (S + B)) % L;
        if (M1 > M2)
            swap(M1, M2);
        // cout << M1 << " " << M2 << endl;
        // for (auto i : cur) {
        //     cout << "[" << i.l << ',' << i.r << "(" << i.col << ")], ";
        // }
        // cout << endl;
        // return 0;
        auto lft = cur.lower_bound({M1, INF, INF});
        auto rght = cur.lower_bound({M2, INF, INF});
        lft--, rght--;
        Seg lval = *lft;
        Seg rval = *rght;
        // cout << "lval: " << lval.l << " " << lval.r << endl;
        // cout << "rval: " << rval.l << " " << rval.r << endl;
        vector<Seg> addSegs;
        addSegs.push_back({lval.l, M1 - 1, lval.col});
        addSegs.push_back({M1, M2, X});
        addSegs.push_back({M2 + 1, rval.r, rval.col});
        while (lft != rght) {
            lft = erase(lft);
        }
        erase(rght);
        for (auto j : addSegs) {
            add(j);
        }
    }

    // for (auto i : cur) {
    //     cout << i.l << ' ' << i.r << ' ' << i.col << endl;
    // }
    ll ans = 0;
    for (ll i = 0; i < C; i++) {
        // cout << numColor[i] << ' ';
        ans = max(ans, numColor[i]);
    }
    // cout << endl;
    cout << ans << endl;
}