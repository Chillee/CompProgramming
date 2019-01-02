#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;
int N, K;
int A[MAXN];
int main() {
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    sort(A, A + N);
    int ans = 0;
    int cur = 0;
    for (int i = 0; i < N - 1; i++) {
        while (cur < N && A[cur] <= A[i])
            cur++;
        if (cur >= N)
            break;
        if (A[cur] - A[i] <= K && A[cur] > A[i]) {
            ans++;
        }
    }
    cout << N - ans << endl;
}