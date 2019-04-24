#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef array<ull, 2> hash_t;
namespace std {
template <> struct hash<hash_t> {
    inline size_t operator()(const hash_t &v) const { return v[0] * 31 + v[1]; }
};
} // namespace std

hash_t mods = {(int)1e9 + 9, (int)1e9 + 7}; // 1e9+13
hash_t norm(hash_t x) { return {(x[0] + mods[0]) % mods[0], (x[1] + mods[1]) % mods[1]}; }
#define OP(o, tr, l, r) \
    hash_t operator o(hash_t a, tr b) { return norm({a[0] o b l, a[1] o b r}); }
OP(+, hash_t, [0], [1]) OP(-, hash_t, [0], [1]) OP(*, hash_t, [0], [1]) OP(+, ull, , ) OP(*, ull, , );

struct RollingHash {
    ull p = 29;
    vector<hash_t> ha = {{0, 0}};
    vector<hash_t> pw = {{1, 1}};
    hash_t add(int x) {
        int l = ha.size() - 1;
        ha.push_back(ha[l] * p + (x + 1)), pw.push_back(pw[l] * p);
        return ha.back();
    }
    hash_t interval(int a, int b) { // hash [a, b)
        return ha[b] - ha[a] * pw[b - a];
    }
};

string S;
int K;
bool alphabet[26];
unordered_set<hash_t> cnt;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> S;
    string t;
    cin >> t;
    cin >> K;
    for (int i = 0; i < 26; i++) {
        alphabet[i] = (t[i] == '0');
    }
    for (int l = 0; l < S.size(); l++) {
        int cur = 0;
        auto hash = RollingHash();
        for (int r = l; r < S.size(); r++) {
            cur += alphabet[S[r] - 'a'];
            if (cur > K) {
                break;
            }

            cnt.insert(hash.add(S[r]));
        }
    }
    cout << cnt.size() << endl;
}