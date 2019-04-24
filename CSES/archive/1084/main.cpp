#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;
int N, M, K;
int A[MAXN], B[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M >> K;
    for (int i = 0; i < N; i++)
        cin >> A[i];
    for (int i = 0; i < M; i++)
        cin >> B[i];
    sort(A, A + N), sort(B, B + M);

    int cnt = 0;
    int lidx = 0, ridx = 0;
    while (lidx < N && ridx < M) {
        if (abs(A[lidx] - B[ridx]) <= K) {
            lidx++, ridx++, cnt++;
        } else if (A[lidx] > B[ridx])
            ridx++;
        else
            lidx++;
    }
    cout << cnt << endl;
}