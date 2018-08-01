#include <bits/stdc++.h>

using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

#define unordered_map gp_hash_table
typedef long long ll;
unsigned hash_f(unsigned x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}
struct chash {
    ll operator()(ll x) const { return hash_f(x); }
};

ll N, M, P, Q;
const ll MOD = 1e9 + 7;
unordered_map<ll, ll, chash> seg;

ll get(ll x) { return (seg.find(x) == seg.end()) ? 0 : seg[x]; }
void modify(ll p, ll val) {
    for (seg[p += N] = val; p > 0; p >>= 1) {
        seg[p >> 1] = (get(p) + get(p ^ 1)) % MOD;
    }
}

ll query(ll l, ll r) {
    ll res = 0;
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            res = (get(l++) + res) % MOD;
        if (r & 1)
            res = (get(--r) + res) % MOD;
    }
    return res;
}

struct node;
node *newNode();

struct node {
    ll lv, rv, sum;
    node *left, *right;

    node() : left(NULL), right(NULL), sum(0) {}

    inline void init(ll l, ll r) {
        lv = l;
        rv = r;
    }

    inline void extend() {
        if (!left) {
            ll m = (lv + rv) / 2;
            left = newNode();
            right = newNode();
            left->init(lv, m);
            right->init(m + 1, rv);
        }
    }

    ll getSum(ll l, ll r) {
        if (r < lv || rv < l) {
            return 0;
        }

        if (l <= lv && rv <= r) {
            return sum;
        }

        extend();
        return left->getSum(l, r) + right->getSum(l, r);
    }

    void update(ll p, ll newVal) {
        if (lv == rv) {
            sum = newVal;
            return;
        }

        extend();
        (p <= left->rv ? left : right)->update(p, newVal);
        sum = left->sum + right->sum;
    }
};

ll bufSize = 5e7;
node buf[(int)5e7];
node *newNode() { return &buf[--bufSize]; }

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    P = 91, Q = 47;
    node *rmq = newNode();
    rmq->init(0, 1e9);
    for (ll i = 0; i < M; i++) {
        char t;
        cin >> t;
        if (t == '!') {
            ll a, b;
            cin >> a >> b;
            // modify((a + P) % N, (b + Q) % MOD);
            rmq->update((a + P) % N, (b + Q) % MOD);
        } else {
            ll a, b;
            cin >> a >> b;
            a = (a + P) % N;
            b = (b + Q) % N;

            if (a > b)
                swap(a, b);
            ll Z = rmq->getSum(a, b + 1);
            cout << Z << endl;
            P = ((P * 31) + Z) % MOD;
            Q = ((Q * 29) + Z) % MOD;
        }
    }
}