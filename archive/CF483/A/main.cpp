#include <bits/stdc++.h>

using namespace std;

int N;
int A[1005];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    sort(A, A + N);
    if (N % 2 == 1) {
        cout << A[N / 2] << endl;
    } else {
        cout << A[N / 2 - 1] << endl;
    }
}