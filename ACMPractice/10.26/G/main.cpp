#include <bits/stdc++.h>

#define endl '\n';
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

const int INF = 1e8 + 5;
const int RANDOM = (uint64_t)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
unsigned hash_f(unsigned x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}
unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }
struct chash {
    int operator()(int x) const { return hash_f(x); }
};
const int MAXN = 2e5 + 5;
int N, K;
int A[MAXN];
gp_hash_table<int, int, chash> seg;

int get(int x) { return (seg.find(x) == seg.end()) ? 0 : seg[x]; }
void modify(int p, int val) {
    for (seg[p += N] += val; p > 0; p >>= 1) {
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
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    int ans = 0;
    for (int i = 0; i < N; i += 2) {
        if (i >= (K + 1) / 2) {
            modify(A[i - (K + 1) / 2], -1);
        }
        if (i >= (K + 1) / 2) {
        }
        modify(A[i], 1);
    }
}