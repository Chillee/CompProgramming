#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;
int N, Q;
array<int, 3> queries[MAXN];
template <typename T> struct Seg {
    const int N;
    vector<T> seg;
    T unit;
    inline int combine(int a, int b) { return a + b; }
    Seg(int n, T arr[], T u) : N(n), unit(u), seg(N * 2) {
        for (int i = 0; i < N; i++)
            seg[i + N] = arr[i];
        build();
    }
    void build() {
        for (int i = N - 1; i > 0; --i)
            seg[i] = combine(seg[i << 1], seg[i << 1 | 1]);
    }

    void modify(int p, int val) {
        for (seg[p += N] += val; p > 0; p >>= 1)
            seg[p >> 1] = combine(seg[p], seg[p ^ 1]);
    }

    T query(int l, int r) {
        T resl = unit;
        T resr = unit;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                resl = combine(resl, seg[l++]);
            if (r & 1)
                resr = combine(seg[--r], resr);
        }
        return combine(resl, resr);
    }
};
Seg<int> *seg;
int sals[MAXN];
int initSeg[4 * MAXN];
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

struct chash {
    static unsigned long long hash_f(unsigned long long x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    static unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }
    int operator()(int x) const { return hash_f(x); }
};
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> Q;
    for (int i = 0; i < N; i++)
        cin >> sals[i];
    for (int i = 0; i < Q; i++) {
        char t;
        int a, b;
        cin >> t >> a >> b;
        if (t == '!')
            a--;
        queries[i] = {t == '?', a, b};
    }
    // map<int, int> comp;
    vector<int> vals;
    for (int i = 0; i < N; i++)
        vals.push_back(sals[i]);
    // comp[sals[i]];
    for (int i = 0; i < Q; i++)
        vals.push_back(queries[i][1]), vals.push_back(queries[i][2]);
    sort(vals.begin(), vals.end());
    vals.resize(unique(vals.begin(), vals.end()) - vals.begin());

    unordered_map<int, int, chash> comp;
    for (int i = 0; i < vals.size(); i++)
        comp[vals[i]] = i;
    for (int i = 0; i < N; i++)
        sals[i] = comp[sals[i]];
    for (int i = 0; i < Q; i++) {
        if (queries[i][0] == 1) {
            queries[i][1] = comp[queries[i][1]];
            queries[i][2] = comp[queries[i][2]];
        } else {
            queries[i][2] = comp[queries[i][2]];
        }
    }
    for (int i = 0; i < N; i++)
        initSeg[sals[i]]++;
    seg = new Seg<int>(vals.size(), initSeg, 0);
    for (int i = 0; i < Q; i++) {
        if (queries[i][0] == 1) {
            cout << seg->query(queries[i][1], queries[i][2] + 1) << '\n';
        } else {
            seg->modify(sals[queries[i][1]], -1);
            sals[queries[i][1]] = queries[i][2];
            seg->modify(sals[queries[i][1]], 1);
        }
    }
}