#include <bits/stdc++.h>

using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

const int RANDOM = (uint64_t)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
unsigned hash_f(unsigned x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}
unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }
struct chash {
    int operator()(array<int, 2> x) const { return hash_combine(hash_f(x[0]), hash_f(x[1])); }
};
int T, K;
string A, B;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int t = 0; t < T; t++) {
        gp_hash_table<array<int, 2>, null_type, chash> foundB;
        int t0, t1;
        cin >> t0 >> t1 >> K;
        cin >> B >> A;
        for (int i = K - 1; i < B.size(); i++) {
            foundB.insert({B[i - K + 1] - 'a', B[i] - 'a'});
        }
        int foundA[26];
        fill(begin(foundA), end(foundA), 0);

        long long ans = 0;
        for (int i = 0; i < A.size(); i++) {
            foundA[A[i] - 'a']++;
            for (int j = 0; j < 26; j++) {
                if (foundB.find({j, A[i] - 'a'}) != foundB.end()) {
                    ans += foundA[j];
                }
            }
        }
        cout << ans << endl;
    }
}