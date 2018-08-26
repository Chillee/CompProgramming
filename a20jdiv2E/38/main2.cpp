#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAXN = 1e5 + 5;
const ll MAXBIT = 18;
ll N, M;

ll A[MAXN];
struct Node;
Node *newNode();
struct Node {
    Node *pl, *pr;
    ll nl = 0, nr = 0;
    ll lrun = 0, rrun = 0, val = 0;
    bool isFull = 0;

    void updateVal() {
        lrun = 0, rrun = 0, val = 0, isFull = false;
        val = pl->val + pr->val;
        if (pl->isFull && pr->isFull) {
            isFull = true;
            return;
        }
        isFull = false;
        if (pl->isFull) {
            lrun = (pl->nr - pl->nl) + pr->lrun;
            rrun = pr->rrun;
        } else if (pr->isFull) {
            lrun = pl->lrun;
            rrun = (pr->nr - pr->nl) + pl->rrun;
        } else {
            lrun = pl->lrun;
            rrun = pr->rrun;
            val += (pl->rrun + pr->lrun) * (pl->rrun + pr->lrun + 1) / 2;
        }
    }

    void build(ll l, ll r, ll b) {
        nl = l, nr = r;
        if (nl + 1 == nr) {
            isFull = (A[nl] & (1 << b)) != 0;
            return;
        }
        (pl = newNode())->build(nl, nl + nr >> 1, b);
        (pr = newNode())->build(nl + nr >> 1, nr, b);
        updateVal();
    }
    void modify(ll p, ll x) {
        if (p < nl || nr <= p) {
            return;
        }
        if (nl + 1 == nr) {
            isFull = x;
            return;
        }
        pl->modify(p, x);
        pr->modify(p, x);
        updateVal();
    }
};

ll bufSize = MAXN * 2 * MAXBIT;
Node buf[MAXN * 2 * MAXBIT];
Node *newNode() { return &buf[--bufSize]; }
Node *seg[MAXBIT];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for (ll i = 0; i < N; i++) {
        cin >> A[i];
    }
    for (ll b = 0; b < MAXBIT; b++) {
        seg[b] = newNode();
        seg[b]->build(0, N, b);
    }
    for (ll i = 0; i < M; i++) {
        ll p, v;
        cin >> p >> v;
        p--;
        for (ll b = 0; b < MAXBIT; b++) {
            seg[b]->modify(p, (v & (1 << b)) != 0);
        }
        ll ans = 0;
        for (ll b = 0; b < MAXBIT; b++) {
            ll cur = (seg[b]->val + (seg[b]->lrun * (seg[b]->lrun + 1)) / 2 + (seg[b]->rrun * (seg[b]->rrun + 1)) / 2);
            cur += (seg[b]->isFull) * (seg[b]->nr - seg[b]->nl) * (seg[b]->nr - seg[b]->nl + 1) / 2;
            ans += cur * (1 << b);
        }
        cout << ans << endl;
    }
}