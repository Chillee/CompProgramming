#include <bits/stdc++.h>

using namespace std;

int T, N;
int grid[105][105];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin >> N;
        int cnt = 1;
        for (int i = 0; i < 2 * N - 1; i++) {
            for (int j = 0; j <= i; j++) {
                if (j >= 0 && j < N && i - j >= 0 && i - j < N)
                    grid[j][i - j] = cnt++;
            }
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }
}