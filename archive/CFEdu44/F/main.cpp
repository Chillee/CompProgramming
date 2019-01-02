#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 5;

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

int N, M;
string S;
hash_t hashes[26][MAXN];
vector<int> ords[MAXN];
hash_t baseHash[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    cin >> S;
    vector<int> curOrds;
    for (int i = 0; i < 26; i++) {
        curOrds.push_back(i);
    }
    for (int i = N - 1; i >= 0; i--) {
        curOrds.erase(find(curOrds.begin(), curOrds.end(), S[i] - 'a'));
        curOrds.insert(curOrds.begin(), S[i] - 'a');
        ords[i] = curOrds;
    }
    auto curHash = RollingHash();
    for (int i = 0; i <= N; i++) {
        baseHash[i] = curHash.getPows();
        curHash.add('a');
    }
    for (int i = 0; i < 26; i++) {
        RollingHash curHash = RollingHash();
        for (int j = 0; j <= N; j++) {
            hashes[i][j] = curHash.getHash();
            curHash.add(S[j] - 'a' == i ? 1 : 0);
        }
    }

    for (int i = 0; i < M; i++) {
        int x, y, l;
        cin >> x >> y >> l;
        x--, y--;
        bool isGood = true;
        for (int j = 0; j < 26; j++) {
            hash_t left = (hashes[ords[x][j]][x + l] - hashes[ords[x][j]][x]) * baseHash[N - x];
            hash_t right = (hashes[ords[y][j]][y + l] - hashes[ords[y][j]][y]) * baseHash[N - y];
            if (left != right) {
                isGood = false;
                break;
            }
        }
        if (isGood) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}