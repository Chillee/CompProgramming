#include <bits/stdc++.h>

using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

typedef long long ll;
random_device rd;
mt19937 rng(0);
uniform_int_distribution<ll> uni(1, 1e9);
typedef pair<ll, ll> pii;

const int rdseed =
    (uint64_t)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();

int hash_f(int x) { return ((x >> 16) ^ x) * 0x45d9f3b; }

struct chash {
    int operator()(int x) const { return hash_f(x); }
};

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

ll N = 1e9;
ll NUM_ELEM = 1e5;
ll NUM_QUERIES = 1e5;

gp_hash_table<ll, ll, chash> seg;

ll get(ll x) { return (seg.find(x) == seg.end()) ? 0 : seg[x]; }
void modify(ll p, ll val) {
    for (seg[p += N] = val; p > 0; p >>= 1) {
        seg[p >> 1] = get(p) + get(p ^ 1);
    }
}

ll query(ll l, ll r) {
    ll res = 0;
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            res += get(l++);
        if (r & 1)
            res += get(--r);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<pii> elems;
    for (ll i = 0; i < NUM_ELEM; i++) {
        elems.push_back({uni(rng), uni(rng)});
    }
    vector<pii> queries;
    for (ll i = 0; i < NUM_QUERIES; i++) {
        ll a = uni(rng), b = uni(rng);
        if (a > b)
            swap(a, b);
        queries.push_back({a, b});
    }
    vector<ll> ans1, ans2;
    clock_t begin;
    for (auto i : elems) {
        modify(i.first, i.second);
    }
    begin = clock();
    for (auto i : queries) {
        ans2.push_back(query(i.first, i.second + 1));
    }
    cout << "policy hash table: " << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;
    seg.clear();
    // node *rmq = newNode();
    // rmq->init(0, 1e9);
    // for (auto i : elems) {
    //     rmq->update(i.first, i.second);
    // }
    // begin = clock();
    // for (auto i : queries) {
    //     ans1.push_back(rmq->getSum(i.first, i.second));
    // }
    // cout << "pointer: " << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;
    // for (int i = 0; i < ans1.size(); i++) {
    //     assert(ans1[i] == ans2[i]);
    // }
}