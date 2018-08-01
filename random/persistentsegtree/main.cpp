#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

const int N = 1e5;
random_device rd;
mt19937 rng(0);
uniform_int_distribution<int> uni(1, N);

typedef pair<int, int> pii;
unsigned hash_f(unsigned x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}
int hash_combine(int a, int b) { return a * 31 + b; }
struct chash {
    int operator()(pii x) const {
        int a = hash_f(x.first);
        int b = hash_f(x.second);
        return hash_combine(a, b);
    }
};

typedef struct node {
    int val, child[2];
} node;

gp_hash_table<pii, node, chash> seg;
int last[2 * N + 5];

void build() {
    for (int i = N - 1; i > 0; i--)
        seg[{i, 0}].val = seg[{i << 1, 0}].val + seg[{i << 1 | 1, 0}].val;
}

void modify(int p, int val, int t) {
    for (seg[{p += N, t}].val = val; p > 1; p >>= 1) {
        last[p] = t;
        int childs[2] = {t, last[p ^ 1]};
        seg[{p >> 1, t}] = {seg[{p, t}].val + seg[{p ^ 1, last[p ^ 1]}].val, childs[p % 2], childs[(p % 2) ^ 1]};
    }
    last[1] = t;
}

vector<int> getTimes(int x, int t) {
    vector<int> res;
    int h = sizeof(int) * 8 - __builtin_clz(N);
    for (int s = h - 1; s >= 0; s--) {
        res.push_back(t);
        t = seg[{x >> s, t}].child[(x >> (s + 1)) % 2];
    }
    reverse(res.begin(), res.end());
    return res;
}

int query(int l, int r, int t) {
    int res = 0;
    vector<int> lts = getTimes(l + N, t), rts = getTimes(r + N, t);
    int idx = 0;
    for (l += N, r += N; l < r; l >>= 1, r >>= 1, idx++) {
        if (l & 1)
            res += seg[{l++, lts[idx]}].val;
        if (r & 1)
            res += seg[{--r, rts[idx]}].val;
    }
    return res;
}

const int NUM_MODIFICATIONS = 1e5;
const int NUM_QUERIES = 1e5;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    clock_t begin;
    begin = clock();
    for (int i = 0; i < N; i++) {
        seg[{i + N, 0}] = {uni(rng), 0, 0};
    }
    build();
    cout << "construction: " << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;
    begin = clock();
    for (int i = 1; i < NUM_MODIFICATIONS; i++) {
        modify(i, i, i);
    }
    cout << "modification: " << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;
    begin = clock();
    for (int i = 1; i < NUM_QUERIES; i++) {
        int a = uni(rng);
        int b = uni(rng);
        if (a > b)
            swap(a, b);
        query(a, b, i);
    }
    cout << "query: " << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;
    // for (int)
    // cout << query(0, 4, 0) << " res" << endl;
    // modify(0, 4, 1);
    // // cout << query(0, 4, 0) << " res" << endl;
    // modify(1, 4, 2);
    // modify(3, 4, 2);
    // modify(2, 4, 2);
    // cout << query(0, 4, 0) << " res" << endl;
    // cout << query(0, 4, 1) << " res" << endl;
    // cout << query(0, 4, 2) << " res" << endl;
    // for (int i = 1; i < 2 * N; i++) {
    //     cout << last[i] << ' ';
    // }
    // cout << endl;
    // for (auto i : seg) {
    //     cout << i.first.first << ' ' << i.first.second << ' ' << i.second.val << ' ' << i.second.child[0] << ' '
    //          << i.second.child[1] << endl;
    // }
}