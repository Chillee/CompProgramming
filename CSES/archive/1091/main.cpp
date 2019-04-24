#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;
int N, M;
int H[MAXN], T[MAXN];
multiset<int> curVals;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < N; i++)
        cin >> H[i];
    for (int i = 0; i < M; i++)
        cin >> T[i];
    for (int i = 0; i < N; i++)
        curVals.insert(H[i]);
    for (int i = 0; i < M; i++) {
        auto it = curVals.upper_bound(T[i]);
        it--;
        if (it == curVals.end()) {
            cout << -1 << endl;
            continue;
        }
        cout << *it << endl;
        curVals.erase(it);
    }
}