#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e3 + 5;
int N;
int A[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    if (N == 1) {
        cout << 0 << endl;
        return 0;
    }
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    sort(A, A + N);
    cout << A[N - 1] - A[0] - N + 1 << endl;
}