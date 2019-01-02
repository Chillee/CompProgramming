#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
int N;
array<int, 2> S[MAXN];
array<int, 2> A[MAXN], B[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> S[i][0];
        S[i][1] = i;
    }
    sort(S, S + N);
    for (int i = 0; i < N / 3; i++) {
        A[i][0] = B[i][0] = S[i][1];
        A[i][1] = i;
        B[i][1] = S[i][0] - A[i][1];
    }
    for (int i = N / 3; i < 2 * N / 3; i++) {
        A[i][0] = B[i][0] = S[i][1];
        B[i][1] = i;
        A[i][1] = S[i][0] - B[i][1];
    }
    for (int i = 2 * N / 3; i < N; i++) {
        A[i][0] = B[i][0] = S[i][1];
        B[i][1] = N - i - 1;
        A[i][1] = S[i][0] - B[i][1];
    }
    sort(A, A + N), sort(B, B + N);
    cout << "YES" << endl;
    for (int i = 0; i < N; i++)
        cout << A[i][1] << " ";
    cout << endl;
    for (int i = 0; i < N; i++)
        cout << B[i][1] << " ";
    cout << endl;
}