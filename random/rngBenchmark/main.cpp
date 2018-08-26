#include <bits/stdc++.h>

using namespace std;

auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rng0(seed);
minstd_rand rng1(seed);
const int ITERS = 1e8;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    clock_t begin;
    begin = clock();
    for (int i = 0; i < ITERS; i++) {
        rng0();
    }
    cout << "rng0: " << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;
    begin = clock();
    for (int i = 0; i < ITERS; i++) {
        rng1();
    }
    cout << "rng1: " << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;
}