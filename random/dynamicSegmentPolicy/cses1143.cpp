#include <bits/stdc++.h>

using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

unsigned hash_f(unsigned x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}
struct chash {
    int operator()(int x) const { return hash_f(x); }
};

const int INF = 1e9 + 5;
const int MAXN = 2 * 1e5 + 5;
gp_hash_table<int, int, chash> seg;
gp_hash_table<int, set<int>, chash> elems;
int N, M;
int H[MAXN];
int R[MAXN];

int get(int x) { return (seg.find(x) == seg.end()) ? INF : seg[x]; }
void modify(int p, int val) {
    for (seg[p += INF] = val; p > 0; p >>= 1) {
        seg[p >> 1] = min(get(p), get(p ^ 1));
    }
}

int query(int l, int r) {
    int res = INF;
    for (l += INF, r += INF; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            res = min(res, get(l++));
        if (r & 1)
            res = min(get(--r), res);
    }
    return res;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> H[i];
    }
    for (int i = 0; i < M; i++) {
        cin >> R[i];
    }
    for (int i = 0; i < N; i++) {
        elems[H[i]].insert(i);
    }
    for (auto i : elems) {
        modify(i.first, *i.second.begin());
    }
    for (int i = 0; i < M; i++) {
        int resIdx = query(R[i], INF);
        if (resIdx == INF) {
            cout << 0 << ' ';
            continue;
        }
        elems[H[resIdx]].erase(*elems[H[resIdx]].begin());
        if (elems[H[resIdx]].size() == 0) {
            modify(H[resIdx], INF);
        } else {
            modify(H[resIdx], *elems[H[resIdx]].begin());
        }
        H[resIdx] -= R[i];
        if (resIdx < *elems[H[resIdx]].begin()) {
            modify(H[resIdx], resIdx);
        }
        elems[H[resIdx]].insert(resIdx);
        cout << resIdx + 1 << ' ';
    }
    cout << endl;
}