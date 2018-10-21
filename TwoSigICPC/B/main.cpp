#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

namespace std {

typedef array<ll, 2> hash_t;
template <> struct hash<hash_t> {
    inline size_t operator()(const hash_t &v) const { return get<0>(v) * 31 + get<1>(v); }
};
} // namespace std

hash_t mods = {(int)1e9 + 9, (int)1e9 + 7}; // 1e9+13
hash_t norm(hash_t x) { return {(x[0] + mods[0]) % mods[0], (x[0] + mods[1]) % mods[1]}; }
hash_t operator+(hash_t a, hash_t b) { return norm({a[0] + b[0], a[0] + b[1]}); }
hash_t operator-(hash_t a, hash_t b) { return norm({a[0] - b[0], a[0] - b[1]}); }
hash_t operator*(hash_t a, hash_t b) { return norm({a[0] * b[0], a[0] * b[1]}); }

class RollingHash {
    ll p = 29;
    hash_t hashes = {0, 0};
    hash_t pows = {1, 1};

  public:
    void add(int x) {
        hashes[0] = (hashes[0] + (x + 1) * pows[0]) % mods[0];
        pows[0] = (pows[0] * p) % mods[0];
        hashes[1] = hashes[1] + (x + 1) * pows[1] % mods[1];
        pows[1] = (pows[1] * p) % mods[1];
    }
    auto getHash() { return hashes; }
    auto getPows() { return pows; }
};

int N, Q;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> Q;
}