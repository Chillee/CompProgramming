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
    int operator()(int x) const { return hash_f(x); }
};
const int MAXN = 1e5 + 5;
int T;
int N, Q;
gp_hash_table<int, int, chash> curVals;
int A[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int t = 0; t < T; t++) {
        curVals.clear();
        cin >> N >> Q;
        for (int i = 0; i < N; i++) {
            cin >> A[i];
            curVals[A[i]]++;
        }
        for (int i = 0; i < Q; i++) {
            int t;
            cin >> t;
            if (t == 1) {
                int p, v;
                cin >> p >> v;
                p--;
                curVals[A[p]]--;
                if (curVals[A[p]] == 0)
                    curVals.erase(A[p]);
                A[p] = v;
                curVals[A[p]]++;
            } else {
                cout << curVals.size() - (curVals.find(0) != curVals.end()) << endl;
            }
        }
    }
}