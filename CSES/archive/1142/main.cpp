#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5e5 + 5;
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
int N;
int board[MAXN];
template <typename T> struct Seg {
    const int N;
    vector<int> seg;
    T unit;
    const function<T(T, T)> combine;
    Seg(int n, T u, function<T(T, T)> cF) : N(n), unit(u), combine(cF) { seg.assign(2 * N, unit); }
    int get(int x) { return seg[x]; }

    void modify(int p, T value) {
        p += N;
        for (seg[p] = value; p > 0; p >>= 1) {
            seg[p >> 1] = combine(get(p), get(p ^ 1));
        }
    }

    T query(int l, int r) {
        T resl = unit;
        T resr = unit;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                resl = combine(resl, get(l++));
            if (r & 1)
                resr = combine(get(--r), resr);
        }
        return combine(resl, resr);
    }
};
int lft[MAXN];
map<int, int> comp, decomp;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    Seg<int> mxSeg(MAXN, -1, [](int a, int b) { return max(a, b); });
    Seg<int> mnSeg(MAXN, N, [](int a, int b) { return min(a, b); });
    for (int i = 0; i < N; i++)
        cin >> board[i];
    for (int i = 0; i < N; i++)
        comp[board[i]] = 0;
    int idx = 0;
    for (auto &i : comp) {
        i.second = idx++;
        decomp[i.second] = i.first;
    }
    for (int i = 0; i < N; i++)
        board[i] = comp[board[i]];
    for (int i = 0; i < N; i++) {
        lft[i] = mxSeg.query(0, board[i]);
        mxSeg.modify(board[i], i);
    }
    long long ans = 0;
    for (int i = N - 1; i >= 0; i--) {
        long long rght = mnSeg.query(0, board[i]);
        long long cur = ((i - lft[i] - 1) + (rght - i - 1) + 1) * decomp[board[i]];
        ans = max(ans, cur);
        mnSeg.modify(board[i], i);
    }
    cout << ans << endl;
}