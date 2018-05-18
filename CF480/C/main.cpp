#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
int N, K;
int A[MAXN];
int group[300];

int main() {
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < 300; i++) {
        group[i] = -1;
    }
    for (int i = 0; i < N; i++) {
        if (group[A[i]] != -1) {
            A[i] = group[A[i]];
            continue;
        }
        int minVal = A[i] - K + 1;
        for (int j = A[i]; j > A[i] - K; j--) {
            if (j == -1 || group[j] != -1) {
                if (j == -1) {
                    minVal = 0;
                } else if (A[i] - group[j] >= K) {
                    minVal = j + 1;
                } else {
                    minVal = group[j];
                }
                break;
            }
        }
        for (int j = minVal; j <= A[i]; j++) {
            group[j] = minVal;
        }
        A[i] = minVal;
    }
    for (int i = 0; i < N; i++) {
        cout << A[i] << ' ';
    }
    cout << endl;
}