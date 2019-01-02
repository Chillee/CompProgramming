#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 5;
const int MAXBITS = 23;
const int FLIP = ((1 << (MAXBITS - 1)) - 1);
int N;
int A[MAXN];
int F[1 << MAXBITS];
set<int> vals;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < N; i++) {
        vals.insert(A[i]);
    }
    fill(F, F + (1 << MAXBITS), -1);
    for (auto i : vals) {
        F[i] = i;
    }
    for (int i = 0; i <= MAXBITS; ++i) {
        for (int mask = 0; mask < (1 << MAXBITS); ++mask) {
            if (mask & (1 << i)) {
                F[mask] = max(F[mask], F[mask ^ (1 << i)]);
            }
        }
    }
    for (int i = 0; i < N; i++) {
        cout << F[A[i] ^ FLIP] << ' ';
    }
    cout << endl;
}