#include <bits/stdc++.h>

using namespace std;
const int MAXN = 6e5 + 5;
namespace std {

typedef long long ll;
typedef array<ll, 2> hash_t;
template <> struct hash<hash_t> {
    inline size_t operator()(const hash_t &v) const { return get<0>(v) * 31 + get<1>(v); }
};
} // namespace std

hash_t mods = {(int)1e9 + 9, (int)1e9 + 7}; // 1e9+13
hash_t norm(hash_t x) { return {(x[0] + mods[0]) % mods[0], (x[1] + mods[1]) % mods[1]}; }
hash_t operator+(hash_t a, hash_t b) { return norm({a[0] + b[0], a[1] + b[1]}); }
hash_t operator-(hash_t a, hash_t b) { return norm({a[0] - b[0], a[1] - b[1]}); }
hash_t operator*(hash_t a, hash_t b) { return norm({a[0] * b[0], a[1] * b[1]}); }

struct RollingHash {
    ll p = 29;
    hash_t hashes = {0, 0};
    hash_t pows = {1, 1};

    void add(int x) {
        hashes[0] = (hashes[0] + (x + 1) * pows[0]) % mods[0];
        pows[0] = (pows[0] * p) % mods[0];
        hashes[1] = (hashes[1] + (x + 1) * pows[1]) % mods[1];
        pows[1] = (pows[1] * p) % mods[1];
    }
    hash_t getHash() { return hashes; }
    hash_t getPows() { return pows; }
};
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

struct chash {
    const int RANDOM = (long long)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
    static unsigned long long hash_f(unsigned long long x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    static unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }
    int operator()(hash_t x) const { return hash_combine(hash_f(x[0]), hash_f(x[1])); }
};
int N, M;
unordered_set<hash_t, chash> keep;
hash_t cur[MAXN];
hash_t pw[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        RollingHash r;
        for (auto j : s)
            r.add(j - 'a');

        keep.insert(r.getHash());
    }
    for (int t = 0; t < M; t++) {
        string s;
        cin >> s;
        RollingHash r;
        for (int i = 0; i < s.size(); i++) {
            cur[i] = r.getHash();
            pw[i] = r.getPows();
            r.add(s[i] - 'a');
        }
        cur[s.size()] = r.getHash();
        bool found = false;
        hash_t hsh = r.getHash();
        [&]() {
            for (int i = 0; i < s.size(); i++) {
                for (int j = 1; j <= 2; j++) {
                    RollingHash charHash;
                    charHash.add((s[i] - 'a' + j) % 3);
                    auto t = hsh - cur[i + 1] + cur[i] + (charHash.getHash() * pw[i]);
                    if (keep.find(t) != keep.end()) {
                        cout << "YES" << endl;
                        found = true;
                        return;
                    }
                }
            }
        }();
        if (!found)
            cout << "NO" << endl;
    }
}