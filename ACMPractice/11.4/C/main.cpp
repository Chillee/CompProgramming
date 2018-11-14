#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e4 + 5;
const int MAXK = 1e3 + 5;
int K, N;
int A[MAXN];
int cnt[MAXK];
void fail() {
    cout << "*" << endl;
    exit(0);
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> K >> N;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        cnt[A[i]]++;
    }
    if (N % K != 1 && N % K != K - 1 && N % K != 0) {
        cout << "*" << endl;
        return 0;
    }
    if (N < K - 1) {
        cout << "*" << endl;
        return 0;
    }
    int numNeeded = 0;
    if (N % K == 1) {
        numNeeded = (N - 1) / K;
    } else if (N % K == K - 1) {
        numNeeded = (N + 1) / K;
    } else if (N % K == 0) {
        numNeeded = N / K;
        int numLess = 0;
        int numMore = 0;
        int idxMore = 0, idxLess = 0;
        for (int i = 1; i <= K; i++) {
            if (cnt[i] == numNeeded + 1) {
                numMore++;
                idxMore = i;
            } else if (cnt[i] == numNeeded - 1) {
                numLess++;
                idxLess = i;
            }
        }
        if (numMore == 1 && numLess == 1) {
            cout << "-" << idxMore << " +" << idxLess << endl;
        } else {
            fail();
        }
        return 0;
    }
    int numFail = 0;
    int idxFail = 0;
    for (int i = 1; i <= K; i++) {
        if (cnt[i] != numNeeded) {
            numFail++;
            idxFail = i;
        }
    }
    if (numFail > 1 || numFail == 0)
        fail();
    if (N % K == 1) {
        cout << "-" << idxFail << endl;
    } else {
        cout << "+" << idxFail << endl;
    }
    return 0;
}