#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;
int N, K;
char grid[4][MAXN];
int main() {
    cin >> N >> K;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < N; j++) {
            grid[i][j] = '.';
        }
    }
    if (K > (N - 2) * 2) {
        cout << "NO" << endl;
        return 0;
    }
    cout << "YES" << endl;
    for (int i = 1; i < 3; i++) {
        for (int j = 1; j < N / 2; j++) {
            if (K < 2) {
                break;
            }
            int idx1 = N - j - 1;
            int idx2 = j;
            grid[i][idx1] = '#';
            grid[i][idx2] = '#';
            K -= 2;
        }
    }
    for (int i = 1; i < 3; i++) {
        if (K == 0)
            break;
        grid[i][N / 2] = '#';
        K--;
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < N; j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
}