#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
int N;
pii A[20];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        int t;
        cin >> t;
        A[i] = {t, i};
    }
    if (N == 1) {
        cout << -1 << endl;
        return 0;
    }
    sort(A, A + N);
    if (N == 2 && A[0].first == A[1].first) {
        cout << -1 << endl;
        return 0;
    }
    cout << 1 << endl;
    cout << A[0].second + 1 << endl;
}