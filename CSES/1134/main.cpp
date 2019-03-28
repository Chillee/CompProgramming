#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5e5 + 5;
int N;
set<int> cur;
int deg[MAXN];
int A[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N - 2; i++) {
        cin >> A[i];
        A[i]--;
        deg[A[i]]++;
    }
    for (int i = 0; i < N; i++) {
        if (deg[i] == 0)
            cur.insert(i);
    }
    for (int i = 0; i < N - 2; i++) {
        cout << *cur.begin() + 1 << ' ' << A[i] + 1 << endl;
        cur.erase(cur.begin());
        deg[A[i]]--;
        if (deg[A[i]] == 0)
            cur.insert(A[i]);
    }
    cout << *cur.begin() + 1 << ' ';
    cur.erase(cur.begin());
    cout << *cur.begin() + 1 << endl;
}