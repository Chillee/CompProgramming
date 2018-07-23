#include <bits/stdc++.h>

using namespace std;

int N, M;
int C[1005];
int A[1005];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> C[i];
    }
    for (int i = 0; i < M; i++) {
        cin >> A[i];
    }
    int curBill = 0;
    int ans = 0;
    for (int i = 0; i < N; i++) {
        if (curBill >= N) {
            break;
        }
        if (C[i] <= A[curBill]) {
            ans++;
            curBill++;
        }
    }
    cout << ans << endl;
}