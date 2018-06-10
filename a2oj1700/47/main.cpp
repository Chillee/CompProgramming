#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

namespace std {
template <> struct hash<tuple<ll, ll>> {
    inline size_t operator()(const tuple<ll, ll> &v) const { return get<0>(v) * 31 + get<1>(v); }
};
} // namespace std

class RollingHash {
    ll p = 29;
    tuple<ll, ll> mods = {(int)1e9 + 9, (int)1e9 + 7}; // 1e9+13
    tuple<ll, ll> hashes = {0, 0};
    tuple<ll, ll> pows = {1, 1};

  public:
    void add(char &x) {
        get<0>(hashes) = (get<0>(hashes) + (x - 'a' + 1) * get<0>(pows)) % get<0>(mods);
        get<0>(pows) = (get<0>(pows) * p) % get<0>(mods);
        get<1>(hashes) = get<1>(hashes) + (x - 'a' + 1) * get<1>(pows) % get<1>(mods);
        get<1>(pows) = (get<1>(pows) * p) % get<1>(mods);
    }
    auto getHash() { return hashes; }
};

string S;
int K;
bool alphabet[26];
unordered_set<tuple<ll, ll>> cnt;

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
            hash.add(S[r]);
            if (cur > K) {
                break;
            }
            cnt.insert(hash.getHash());
        }
    }
    cout << cnt.size() << endl;
}