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
    unsigned operator()(array<int, 26> x) const {
        unsigned res = 1;
        for (int i = 0; i < 26; i++) {
            res = hash_combine(res, hash_f(x[i]));
        }
        return res;
    }
};
const int MAXN = 1e3 + 5;
int T;
array<int, 26> cntA[MAXN];
array<int, 26> cntB[MAXN];
array<int, 26> diff(array<int, 26> a, array<int, 26> b) {
    array<int, 26> res;
    for (int i = 0; i < 26; i++) {
        res[i] = a[i] - b[i];
    }
    return res;
}
gp_hash_table<array<int, 26>, array<int, 2>, chash> aSubs;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int t = 0; t < T; t++) {
        aSubs.clear();
        fill(begin(cntA), end(cntA), array<int, 26>());
        fill(begin(cntB), end(cntB), array<int, 26>());
        string A, B;
        cin >> A >> B;
        for (int i = 1; i <= A.size(); i++) {
            for (int j = 0; j < 26; j++) {
                cntA[i][j] = cntA[i - 1][j];
            }
            cntA[i][A[i - 1] - 'a']++;
        }
        for (int i = 1; i <= B.size(); i++) {
            for (int j = 0; j < 26; j++) {
                cntB[i][j] = cntB[i - 1][j];
            }
            cntB[i][B[i - 1] - 'a']++;
        }
        for (int i = 0; i < A.size(); i++) {
            for (int j = i + 1; j <= A.size(); j++) {
                auto key = diff(cntB[j], cntB[i]);
                if (aSubs.find(key) == aSubs.end()) {
                    aSubs[key] = {i, j};
                }
            }
        }
        bool done = false;
        for (int d = A.size(); d > 0; d--) {
            if (done)
                break;
            for (int i = 0; i < A.size(); i++) {
                if (i + d > A.size())
                    continue;
                if (done)
                    break;
                // cout << i << ' ' << i + d << endl;
                auto key = diff(cntA[i + d], cntA[i]);
                if (aSubs.find(key) != aSubs.end()) {
                    auto res = aSubs[key];
                    // cout << res[0] << ' ' << res[1] << endl;
                    for (int j = i; j < i + d; j++) {
                        cout << A[j];
                    }
                    cout << endl;
                    done = true;
                }
            }
        }
        if (!done)
            cout << "NONE" << endl;
    }
}