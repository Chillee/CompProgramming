#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;
int N, M;
int A[MAXN][MAXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            char t;
            cin >> t;
            if (t == '.') {
                A[i][j] = 0;
            } else if (t == '*') {
                A[i][j] = -1;
            } else {
                A[i][j] = t - '0';
            }
        }
    }
    vector<int> dx = {-1, 0, 1};
    vector<int> dy = {-1, 0, 1};
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (A[i][j] >= 0) {
                int cnt = A[i][j];
                for (auto x : dx) {
                    for (auto y : dy) {
                        if (A[i + x][j + y] == -1)
                            cnt--;
                    }
                }
                if (cnt != 0) {
                    cout << "NO" << endl;
                    return 0;
                }
            }
        }
    }
    cout << "YES" << endl;
}