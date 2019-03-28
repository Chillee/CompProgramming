#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

typedef bitset<100> b100;
struct chash {
    const int RANDOM = (long long)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
    static unsigned long long hash_f(unsigned long long x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    static unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }
    int operator()(b100 x) const {
        int cur = 1;
        for (int i = 0; i < x.size(); i++)
            cur = hash_combine(cur, hash_f(x[i]));
        return cur ^ RANDOM;
    }
};
inline b100 modm(b100 x, b100 mask, int m) { return ((x >> m) ^ x) & mask; }
const int mxM = 19;
int main() {
    int m;
    scanf("%d", &m);
    unordered_map<b100, long long, chash> gt;
    b100 p1(1), p2(0), p3(1), p4(0), mask;
    for (int i = 0; i < m; i++)
        mask.set(i);
    for (long long i = 0; i < (1 << mxM); i++) {
        if (gt.find((p1 << m) | p2) == gt.end())
            gt[(p1 << m) | p2] = i;
        p2 ^= modm(p1 << 1, mask, m);
        swap(p1, p2);
    }
    long long ans = 1LL << 50;
    long long k = (1 << mxM) % m;
    for (long long i = 0; i < (1 << mxM); i++) {
        if (gt.find((p4 << m) | p3) != gt.end())
            ans = min(ans, gt[(p4 << m) | p3] + (i << mxM));
        p3 ^= modm(p1 << k, mask, m);
        p4 ^= modm(p2 << k, mask, m);
        swap(p1, p3);
        swap(p2, p4);
    }
    printf("%lld\n", ans + 1);
    return 0;
}