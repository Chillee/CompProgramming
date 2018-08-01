#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

unsigned hash_f(unsigned x) { return ((x >> 16) ^ x) * 0x45d9f3b; }

struct chash {
    int operator()(int x) const { return hash_f(x); }
};

int N = 1e9;
gp_hash_table<int, int, chash> seg;

int get(int x) { return (seg.find(x) == seg.end()) ? 0 : seg[x]; }
void modify(int p, int val) {
    for (seg[p += N] = val; p > 0; p >>= 1) {
        seg[p >> 1] = get(p) + get(p ^ 1);
    }
}

int query(int l, int r) {
    int res = 0;
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
    int idx = 1;
    for (int i = 0; i < 8; i++) {
        modify(idx, i);
        idx *= 10;
    }
    cout << query(0, 1e7 + 1) << endl;
}