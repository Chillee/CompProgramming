#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2005;
char grid[MAXN][MAXN];
int cnts[MAXN];
int N, M;
int main() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> grid[i][j];
        }
    }
    for (int j = 0; j < M; j++) {
        int cnt = 0;
        for (int i = 0; i < N; i++) {
            if (grid[i][j] == '1')
                cnt++;
        }
        cnts[j] = cnt;
    }
    for (int i = 0; i < N; i++) {
        bool unnecessary = true;
        for (int j = 0; j < M; j++) {
            if (cnts[j] == 1 && grid[i][j] == '1') {
                unnecessary = false;
                break;
            }
        }
        if (unnecessary) {
            cout << "YES" << endl;
            return 0;
        }
    }
    cout << "NO" << endl;
}