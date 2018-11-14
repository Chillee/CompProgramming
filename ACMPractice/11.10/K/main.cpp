#include <bits/stdc++.h>

using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

const int RANDOM = (long long)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
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

int N, Q;
gp_hash_table<int, int, chash> pos;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> Q;
    for (int i = 0; i < N; i++) {
        int t;
        cin >> t;
        pos[i] += t;
    }
    for (int i = 0; i < Q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int c, x;
            cin >> c >> x;
            c--;
            pos[c] = x;
        } else {
            int a, b;
            cin >> a >> b;
            a--, b--;
            cout << abs(pos[a] - pos[b]) << endl;
        }
    }
}