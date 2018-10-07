#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

using namespace std;

const int MAX_BIT = 10;

const int RANDOM =
    (uint64_t)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
unsigned hash_f(unsigned x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}
unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }

unsigned int chash(set<int> x, int limit) {
    int cur = 1;
    for (auto i : x) {
        if (i > limit)
            break;

        cur = hash_combine(cur, i);
    }
    return cur;
};

const int MAXN = 63;
int H;
vector<set<int>> sets[MAXN];
gp_hash_table<int, int> G[MAXN];

void rec(set<int> &cur, int sum, int val, int n) {
    for (int i = val; i <= n; i++) {
        if (cur.find(i) == cur.end() && sum + i <= 60 - n) {
            cur.insert(i);
            sum += i;
            sets[n].push_back(cur);
            rec(cur, sum, i, n);
            sum -= i;
            cur.erase(i);
        }
    }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // cin >> H;
    int tot = 0;
    int res = 0;
    for (int i = 0; i <= 60; i++) {
        sets[i].resize(1);
        set<int> cur;
        rec(cur, 0, 1, i);
        cout << i << ' ' << sets[i].size() << endl;
        res += sets[i].size();
    }
    cout << res << endl;

    set<int> emptySet;
    G[0][chash(emptySet, 0)] = 0;
    for (int i = 1; i < MAXN; i++) {
        for (auto s : sets[i]) {
            set<int> mex;
            for (int j = 1; j <= i; j++) {
                if (s.find(j) == s.end()) {
                    if (j <= i - j)
                        s.insert(j);
                    assert(G[i - j].find(chash(s, i - j)) != G[i - j].end());
                    mex.insert(G[i - j][chash(s, i - j)]);
                    if (j <= i - j)
                        s.erase(j);
                }
            }
            for (int j = 0; j <= 60; j++) {
                if (mex.find(j) == mex.end()) {
                    G[i][chash(s, i)] = j;
                    break;
                }
            }
        }
    }
    for (int i = 0; i <= 60; i++) {
        cout << G[i][chash(emptySet, MAXN)] << endl;
    }
}