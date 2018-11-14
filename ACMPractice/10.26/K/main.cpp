#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

const int MAXN = 2e5 + 5;
int N, M;
int A[MAXN];
int binSearch(int l, int r) {
    if (l == r - 1) {
        return l + 1;
    }
    int mid = (l + r) / 2;
    int budget = mid;
    int cur = 0;
    for (int i = 0; i < N; i++) {
        if (A[i] > cur && budget > 0) {
            budget--;
            cur++;
        } else if (A[i] <= cur) {
            cur++;
        }
    }
    if (cur >= M) {
        return binSearch(l, mid);
    } else {
        return binSearch(mid, r);
    }
    cout << cur << endl;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    cout << binSearch(-1, N) << endl;
}