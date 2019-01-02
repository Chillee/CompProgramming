#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500;
int K, a, b;
int grid[MAXN][MAXN];
int tile[MAXN][MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> K;
    // for (int K = 1; K <= 1000; K++) {
    //     bool res = [&]() {
    for (int n = 1; n <= MAXN; n++) {
        for (int a = 1; a <= MAXN; a++) {
            // cout << n << endl;
            if (K % a != 0)
                continue;
            int b = K / a;
            if (n % a != 0 || n % b != 0)
                continue;
            for (int i = 0; i < K; i++) {
                tile[i / b][i % b] = i + 1;
            }
            for (int i = 0; i < n; i += a)
                for (int j = 0; j < n; j += b)
                    for (int k = 0; k < a; k++)
                        for (int l = 0; l < b; l++)
                            grid[i + k][j + l] = tile[k][l];

            cout << n << endl;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++)
                    cout << grid[i][j] << ' ';
                cout << endl;
            }
            return true;
        }
    }
    return false;
    // }();
    // if (!res) {
    //     cout << K << endl;
    // }
    // }
}