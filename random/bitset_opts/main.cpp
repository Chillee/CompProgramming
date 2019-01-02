#include <bits/stdc++.h>

using namespace std;

int hamming1(int a, int b) {
    int d = 0;
    for (int i = 0; i < 32; i++) {
        d += (a & (1 << i)) ^ (b & (1 << i));
    }
    return d;
}
int hamming2(int a, int b) { return __builtin_popcount(a ^ b); }
// int hamming3
const int ITERS = 1e8;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<int> res1, res2;
    for (int i = 0; i < ITERS; i++) {
        res1.push_back(rand());
        res2.push_back(rand());
    }
    int ans = 0;
    clock_t begin = clock();
    for (int i = 0; i < ITERS; i++) {
        ans += hamming1(res1[i], res2[i]);
    }
    cout << ans << endl;
    cout << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;
}