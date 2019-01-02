#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e3 + 5;
int N, A, B;
int grid[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin >> N >> A >> B;
    if (A > 1 && B > 1) {
        cout << "NO" << endl;
        return 0;
    }
    if (N == 2) {
        if (A == 1 && B == 1) {
            cout << "NO" << endl;
            return 0;
        }
    }
    if (N == 3) {
        if (A == 1 && B == 1) {
            cout << "NO" << endl;
            return 0;
        }
    }
    for (int i = 0; i < N - max(A, B); i++) {
        grid[i][i + 1] = 1;
        grid[i + 1][i] = 1;
    }
    cout << "YES" << endl;
    if (A >= 1 && B == 1) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << grid[i][j];
            }
            cout << endl;
        }
    } else {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i == j) {
                    cout << 0;
                    continue;
                }
                cout << 1 - grid[i][j];
            }
            cout << endl;
        }
    }
}