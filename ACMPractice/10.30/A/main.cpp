#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;
int N, M, D;
array<int, 2> A[MAXN];
int ans[MAXN];
bool check(int mid) {
    for (int i = mid; i < N; i++) {
        if (A[i][0] - A[i - mid][0] <= D) {
            return false;
        }
    }
    return true;
}
int binSearch(int l, int r) {
    if (l >= r - 2) {
        for (int i = max(1, l - 5); i < r + 5; i++) {
            if (check(i)) {
                return i;
            }
        }
        return r;
    }
    int mid = (l + r) / 2;
    if (check(mid)) {
        return binSearch(l, mid);
    } else {
        return binSearch(mid, r);
    }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M >> D;
    for (int i = 0; i < N; i++) {
        int t;
        cin >> t;
        A[i] = {t, i};
    }
    sort(A, A + N);
    int cur = binSearch(1, M + 1);
    for (int i = 0; i < cur; i++) {
        ans[A[i][1]] = i;
    }
    for (int i = cur; i < N; i++) {
        ans[A[i][1]] = i % cur;
    }
    cout << cur << endl;
    for (int i = 0; i < N; i++) {
        cout << ans[i] + 1 << ' ';
    }
    cout << endl;
}