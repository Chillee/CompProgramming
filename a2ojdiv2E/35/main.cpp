#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAXN = 10;
const ll MOD = 1e9 + 9;

array<ll, 2> coeff[MAXN];
array<ll, 2> scoeff[MAXN];
ll A[MAXN];
struct Node;
Node *newNode();
struct Node {
    Node *pl, *pr;
    ll nl = 0, nr = 0, val = 0, ft = 0, st = 0;

    void updateVal() { val = (pl->val + pr->val) % MOD; }
    void propagate() {
        pl->apply(ft, st);
        pr->apply(ft * coeff[nr - nl >> 1][0] + st * coeff[nr - nl >> 1][1],
                  ft * coeff[(nr - nl >> 1) + 1][0] + st * coeff[(nr - nl >> 1) + 1][1]);
        ft = 0;
        st = 0;
    }
    void apply(ll first, ll second) {
        first %= MOD, second %= MOD;
        ft += first;
        ft %= MOD;
        st += second;
        st %= MOD;
        val = (val + (scoeff[nr - nl][0] * first) % MOD + (scoeff[nr - nl][1] * second) % MOD);
        val %= MOD;
    }

    void build(ll l, ll r) {
        nl = l, nr = r;
        if (nl + 1 == nr) {
            val = A[nl];
            return;
        }
        cout << "cur: " << nl << " " << ((nl + nr) >> 1) << ' ' << nr << endl;
        (pl = newNode())->build(nl, (nl + nr) >> 1);
        (pr = newNode())->build((nl + nr) >> 1, nr);
        updateVal();
    }
    void modify(ll l, ll r, ll ft, ll st) {
        if (l <= nl && nr <= r) {
            apply((coeff[nl - l][0] * ft) % MOD + (coeff[nl - l][1] * st) % MOD,
                  (coeff[nl - l + 1][0] * ft) % MOD + (coeff[nl - l + 1][1] * st) % MOD);
            return;
        }
        if (l >= nr || nl >= r)
            return;
        propagate();
        pl->modify(l, r, ft, st);
        pr->modify(l, r, ft, st);
        updateVal();
    }
    ll query(ll l, ll r) {
        if (l <= nl && r >= nr)
            return val;
        if (l >= nr || nl >= r)
            return 0;
        propagate();
        return (pl->query(l, r) + pr->query(l, r)) % MOD;
    }
};

ll bufSize = MAXN * 2;
Node buf[MAXN * 2];
Node *newNode() { return &buf[--bufSize]; }
Node *seg = newNode();

ll N, M;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for (ll i = 0; i < N; i++) {
        cin >> A[i];
    }
    coeff[0] = {1, 0};
    coeff[1] = {0, 1};
    for (ll i = 2; i < MAXN; i++) {
        coeff[i][0] = coeff[i - 1][0] + coeff[i - 2][0];
        coeff[i][0] %= MOD;
        coeff[i][1] = coeff[i - 1][1] + coeff[i - 2][1];
        coeff[i][1] %= MOD;
    }
    scoeff[0] = {0, 0};
    for (ll i = 1; i < MAXN; i++) {
        scoeff[i][0] = scoeff[i - 1][0] + coeff[i - 1][0];
        scoeff[i][0] %= MOD;
        scoeff[i][1] = scoeff[i - 1][1] + coeff[i - 1][1];
        scoeff[i][1] %= MOD;
    }
    seg->build(0, N);
    for (ll i = 0; i < M; i++) {
        ll t, l, r;
        cin >> t >> l >> r;
        l--, r--;
        if (t == 1) {
            seg->modify(l, r + 1, 1, 1);
        } else {
            cout << seg->query(l, r + 1) << endl;
        }
    }
}