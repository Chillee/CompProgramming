#include <bits/stdc++.h>

using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

typedef long long ll;
random_device rd;
mt19937 rng(0);
uniform_int_distribution<ll> uni(1, 1e9);
typedef pair<ll, ll> pii;

const ll rdseed = (uint64_t)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();

const ll N = 1e18;
const ll NUM_ELEM = 1e5;
const ll NUM_QUERIES = 1e5;
struct Node {
    Node *lp, *rp;
    ll sum;
};
inline ll eval(Node *p) { return p ? p->sum : 0LL; }

const ll bufSize = NUM_ELEM * 31;
Node buf[bufSize];
Node *newNode() {
    static auto ptr = buf;
    return ptr++;
}

ll getSum(Node *cur, ll l, ll r, ll x, ll y) {
    if (!cur || x > r || y < l)
        return 0;
    if (x <= l && r <= y) {
        return cur->sum;
    }
    ll m = (l + r) / 2;
    return getSum(cur->lp, l, m, x, y) + getSum(cur->rp, m + 1, r, x, y);
}
void update(Node *&cur, ll l, ll r, ll pos, ll val) {
    if (!cur)
        cur = newNode();
    if (l == r) {
        cur->sum = val;
    } else {
        ll m = (l + r) / 2;
        if (pos <= m) {
            update(cur->lp, l, m, pos, val);
        } else {
            update(cur->rp, m + 1, r, pos, val);
        }
        cur->sum = eval(cur->lp) + eval(cur->rp);
    }
}
Node *root;

uint64_t hash_f(uint64_t x) {
    x ^= x >> 33;
    x *= 0xff51afd7ed558ccd;
    x ^= x >> 33;
    x *= 0xc4ceb9fe1a85ec53;
    x ^= x >> 33;
    return x;
}
class custom_size_policy : public hash_exponential_size_policy<size_t> {
  public:
    custom_size_policy() : hash_exponential_size_policy(1 << 24, 2) {}
};

struct chash {
    ll operator()(ll x) const { return hash_f(x); }
};

typedef gp_hash_table<ll, ll, chash, equal_to<ll>, direct_mask_range_hashing<ll>, linear_probe_fn<>,
                      hash_standard_resize_policy<custom_size_policy, hash_load_check_resize_trigger<true>, true>>
    gp;

gp seg;
ll get(ll x) {
    auto res = seg.find(x);
    return (res == seg.end()) ? 0 : res->second;
}
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

signed main() {
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
    begin = clock();
    for (auto i : elems) {
        modify(i.first, i.second);
    }
    for (auto i : queries) {
        ans2.push_back(query(i.first, i.second + 1));
    }
    cout << "hash: " << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;
    seg.clear();

    begin = clock();
    for (auto i : elems) {
        update(root, 1, N, i.first, i.second);
    }
    for (auto i : queries) {
        ans1.push_back(getSum(root, 1, N, i.first, i.second));
    }
    cout << "pointer: " << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;
    for (ll i = 0; i < ans1.size(); i++) {
        assert(ans1[i] == ans2[i]);
    }
}