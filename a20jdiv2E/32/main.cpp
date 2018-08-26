#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

typedef array<ll, 2> hash_t;
const ll POW = 1271383;
struct chash {
    uint64_t operator()(const hash_t &v) const { return v[0] * 31ull + v[1]; }
};

hash_t mods = {(ll)1e9 + 9, (ll)1e9 + 7}; // 1e9+13
hash_t norm(hash_t x) { return {(x[0] + mods[0]) % mods[0], (x[1] + mods[1]) % mods[1]}; }
hash_t operator+(hash_t a, hash_t b) { return norm({a[0] + b[0], a[1] + b[1]}); }
hash_t operator-(hash_t a, hash_t b) { return norm({a[0] - b[0], a[1] - b[1]}); }
hash_t operator*(hash_t a, hash_t b) { return norm({a[0] * b[0], a[1] * b[1]}); }

class RollingHash {
    hash_t hashes = {0, 0};
    hash_t pows = {1, 1};

  public:
    void add(ll x) {
        hashes[0] = (hashes[0] + (x + 1) * pows[0]) % mods[0];
        pows[0] = (pows[0] * POW) % mods[0];
        hashes[1] = hashes[1] + (x + 1) * pows[1] % mods[1];
        pows[1] = (pows[1] * POW) % mods[1];
    }
    auto getHash() { return hashes; }
    auto getPows() { return pows; }
};
const ll MAXN = 1e6 + 5;
ll N, M;
vector<ll> adjlist[MAXN];
vector<hash_t> hashes[MAXN];
unordered_map<hash_t, ll, chash> collisions;
vector<array<ll, 2>> edgelist;
hash_t pows[MAXN];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    RollingHash t;
    for (int i = 0; i < MAXN; i++) {
        t.add(0);
        pows[i] = t.getPows();
    }
    cin >> N >> M;
    for (ll i = 0; i < M; i++) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        adjlist[a].push_back(b);
        adjlist[b].push_back(a);
        edgelist.push_back({a, b});
    }
    for (ll i = 0; i < N; i++) {
        RollingHash cur;
        sort(adjlist[i].begin(), adjlist[i].end());
        for (auto j : adjlist[i]) {
            hashes[i].push_back(cur.getHash());
            cur.add(j);
        }
        hashes[i].push_back(cur.getHash());
        collisions[cur.getHash()]++;
    }
    ll ans = 0;
    for (auto i : edgelist) {
        ll locA = lower_bound(adjlist[i[1]].begin(), adjlist[i[1]].end(), i[0]) - adjlist[i[1]].begin();
        ll locB = lower_bound(adjlist[i[0]].begin(), adjlist[i[0]].end(), i[1]) - adjlist[i[0]].begin();
        auto hashApost = *hashes[i[0]].rbegin() - hashes[i[0]][locB + 1];
        auto hashBpost = *hashes[i[1]].rbegin() - hashes[i[1]][locA + 1];
        auto hashAPre = hashes[i[0]][locB];
        auto hashBPre = hashes[i[1]][locA];
        if ((hashAPre * hash_t{POW, POW} + hashApost) == (hashBPre * hash_t{POW, POW} + hashBpost)) {
            ans++;
        }
    }
    for (auto i : collisions) {
        ans += i.second * (i.second - 1) / 2;
    }
    cout << ans << endl;
}