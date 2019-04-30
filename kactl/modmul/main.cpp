#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
typedef long long ll;
using namespace std;

typedef unsigned long long ull;
namespace kactl {
typedef unsigned long long ull;
const int bits = 10;
// if all numbers are less than 2^k, set bits = 64-k
const ull po = 1 << bits;
ull mod_mul(ull a, ull b, ull &c) {
    ull x = a * (b & (po - 1)) % c;
    while ((b >>= bits) > 0) {
        a = (a << bits) % c;
        x += (a * (b & (po - 1))) % c;
    }
    return x % c;
}
} // namespace kactl
namespace int128 {
ll mod_mul(ull a, ull b, ull M) { return (__uint128_t)a * b % M; }
} // namespace int128
namespace simon {
typedef unsigned long long u64;
u64 mod_mul(u64 a, u64 b, u64 c) {
    asm("mul %0\ndiv %2\n" : "+d"(b) : "a"(a), "r"(c));
    return b;
}
} // namespace simon
namespace agent {
typedef unsigned long long ull;
typedef long double ld;
ld mxOver = 0;
ull mod_mul(ull a, ull b, ull M) {
	ll ret = a * b - M * ull(ld(a) * ld(b) / ld(M)+0.5L);
	ull res= ret + M * (ret < 0);
    assert(res == int128::mod_mul(a,b,M));
    return res;
}
} // namespace agent
struct timeit {
    decltype(chrono::high_resolution_clock::now()) begin;
    const string label;
    timeit(string label = "???") : label(label) { begin = chrono::high_resolution_clock::now(); }
    ~timeit() {
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
        cerr << duration << "ms elapsed [" << label << "]" << endl;
    }
};
const int ITERS = 1e7;
mt19937_64 rng(time(0));
uniform_int_distribution<ull> mod(1, (1ull << 63) -1);
uniform_int_distribution<ull> mul(1 , (1ull << 63) - 1);
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // ull a = (1ull << 63) - (1ull << 62), b = (1ull << 63) - 3, c = (1ull << 63) - 1;
    // ull c = 525286406238180630ull;
    // ull a = 5261782527088258156ull;
    // ull b = 2129363616027471090ull;
    // ull c = 6971742765648838167ull;
    // cout << agent::mod_mul(c - 1, c - 1, c) << endl;
    // // cout << int128::mod_mul(a, b, c) << endl;
    // return 0;
    vector<array<ull, 3>> vals;
    for (int i = 0; i < ITERS; i++) {
        vals.push_back({mul(rng), mul(rng), mod(rng)});
        vals.back()[0] %= vals.back()[2];
        vals.back()[1] %= vals.back()[2];
    }
    // {
    //     timeit x("int128");
    //     ull start = 3;
    //     for (int i = 0; i < ITERS; i++) {
    //         start = int128::mod_mul(start + vals[i][0], vals[i][1], vals[i][2]) & 3;
    //     }
    //     cout << start << endl;
    // }
    {
        timeit x("agent");
        ull start = 3;
        for (int i = 0; i < ITERS; i++) {
            start = agent::mod_mul(start + vals[i][0], vals[i][1], vals[i][2]) & 1000;
        }
        cout << start << endl;
    }
    {
        timeit x("tsinghua");
        ull start = 3;
        for (int i = 0; i < ITERS; i++) {
            start = tsinghua::mod_mul(start + vals[i][0], vals[i][1], vals[i][2]) & 1000;
        }
        cout << start << endl;
    }
    // {
    //     timeit x("kactl");
    //     ull start = 3;
    //     for (int i = 0; i < ITERS; i++) {
    //         start = kactl::mod_mul(start + vals[i][0], vals[i][1], vals[i][2]) & 3;
    //     }
    //     cout << start << endl;
    // }
    // {
    //     timeit x("simon");
    //     ull start = 3;
    //     for (int i = 0; i < ITERS; i++) {
    //         start = simon::mod_mul(start + vals[i][0], vals[i][1], vals[i][2]) & 3;
    //     }
    //     cout << start << endl;
    // }
}