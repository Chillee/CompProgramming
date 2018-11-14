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

int n;
int p[1000005];
long long a[1000005];
gp_hash_table<long long, int, chash> cnt;

long long solve(long long k) {
    long long ans = 0;
    for (int j = 61; j >= 0; --j) {
        cnt.clear();
        ans <<= 1;
        for (int i = 1; i <= n; ++i)
            ++cnt[a[i] >> j];
        long long add = 0;
        for (auto v : cnt)
            if (cnt.find(v.first ^ ans) != cnt.end())
                add += 1LL * v.second * cnt[v.first ^ ans];
        if (add < k) {
            k -= add;
            ++ans;
        }
    }
    return ans;
}

int main(void) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    long long k;
    cin >> n >> k;
    for (int i = 2; i <= n; ++i)
        cin >> p[i] >> a[i];
    for (int i = 2; i <= n; ++i)
        a[i] ^= a[p[i]];
    // for (int i = 1; i <= n * n; ++i) cout << solve(i) << ' '; cout << endl;
    cout << solve(k) << endl;
    return 0;
}