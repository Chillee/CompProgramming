#include <bits/stdc++.h>

#define endl '\n';
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

const int RANDOM =
    (uint64_t)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
unsigned hash_f(unsigned x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}
unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }
struct chash {
    int operator()(set<int> x) const {
        int res = 1;
        for (auto i : x) {
            res = hash_combine(res, hash_f(i));
        }
        return res;
    }
};

const int MAXN = 105;
int N;
int card[MAXN][5][5];
gp_hash_table<set<int>, vector<int>, chash> nums;
set<int> cardRows[MAXN * 5];
set<int> setDiff(set<int> setA, set<int> setB) {
    set<int> difference;
    set_difference(setA.begin(), setA.end(), setB.begin(), setB.end(), inserter(difference, difference.end()));
    return difference;
}
set<int> setInter(set<int> setA, set<int> setB) {
    set<int> difference;
    set_intersection(setA.begin(), setA.end(), setB.begin(), setB.end(), inserter(difference, difference.end()));
    return difference;
}

set<int> setUnion(set<int> setA, set<int> setB) {
    set<int> difference;
    set_union(setA.begin(), setA.end(), setB.begin(), setB.end(), inserter(difference, difference.end()));
    return difference;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                cin >> card[i][j][k];
            }
        }
    }
    for (int a = 0; a < N; a++) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                cardRows[a * 5 + i].insert(card[a][i][j]);
            }
            nums[cardRows[a * 5 + i]].push_back(a * 5 + i);
        }
    }
    for (int a = 0; a < N * 5; a++) {
        for (int b = 0; b < N * 5; b++) {
            if (a / 5 == b / 5)
                continue;
            auto setA = cardRows[a];
            auto setB = cardRows[b];
            set<int> shared = setInter(setA, setB);
            if (shared.size() == 0)
                continue;

            set<int> t = setUnion(setA, setB);
            vector<int> total;
            for (auto i : t) {
                total.push_back(i);
            }
            unordered_map<int, int> rowCnts;
            map<int, int> works;
            for (auto i : shared) {
                works[i] = true;
            }
            for (int i = 0; i < (1 << total.size()); i++) {
                set<int> cur;
                for (int j = 0; j < total.size(); j++) {
                    if (i & (1 << j)) {
                        cur.insert(total[j]);
                    }
                }
                // if (display) {
                //     cout << bitset<10>(i) << endl;
                //     for (auto j : cur) {
                //         cout << j << ' ';
                //     }
                //     cout << endl;
                // }
                auto res = nums[cur];
                for (auto j : res) {
                    if (j != a && j != b) {
                        for (int k = 0; k < total.size(); k++) {
                            if ((i & (1 << k)) == 0) {
                                works[total[k]] = false;
                            }
                        }
                        break;
                    }
                }
            }
            for (auto i : shared) {
                if (works[i]) {
                    // cout << a << ' ' << b << ' ' << i << endl;
                    cout << a / 5 + 1 << ' ' << b / 5 + 1 << endl;
                    return 0;
                }
            }
        }
    }
    cout << "no ties" << endl;
}