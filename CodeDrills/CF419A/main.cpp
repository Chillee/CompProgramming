#include <bits/stdc++.h>

using namespace std;

int N, M;
int G[105][105];
vector<int> rows;
vector<int> cols;
int main() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> G[i][j];
        }
    }
    if (N <= M) {
        for (int i = 0; i < N; i++) {
            int mn = 1000;
            for (int j = 0; j < M; j++) {
                mn = min(G[i][j], mn);
            }
            for (int j = 0; j < M; j++) {
                G[i][j] -= mn;
            }
            for (int j = 0; j < mn; j++) {
                rows.push_back(i + 1);
            }
        }
        for (int i = 0; i < M; i++) {
            int mn = 1000;
            for (int j = 0; j < N; j++) {
                mn = min(G[j][i], mn);
            }
            for (int j = 0; j < N; j++) {
                G[j][i] -= mn;
            }
            for (int j = 0; j < mn; j++) {
                cols.push_back(i + 1);
            }
        }
    } else {
        for (int i = 0; i < M; i++) {
            int mn = 1000;
            for (int j = 0; j < N; j++) {
                mn = min(G[j][i], mn);
            }
            for (int j = 0; j < N; j++) {
                G[j][i] -= mn;
            }
            for (int j = 0; j < mn; j++) {
                cols.push_back(i + 1);
            }
        }
        for (int i = 0; i < N; i++) {
            int mn = 1000;
            for (int j = 0; j < M; j++) {
                mn = min(G[i][j], mn);
            }
            for (int j = 0; j < M; j++) {
                G[i][j] -= mn;
            }
            for (int j = 0; j < mn; j++) {
                rows.push_back(i + 1);
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (G[i][j] != 0) {
                cout << -1 << endl;
                return 0;
            }
        }
    }
    cout << rows.size() + cols.size() << endl;
    for (auto i : rows) {
        cout << "row " << i << endl;
    }
    for (auto i : cols) {
        cout << "col " << i << endl;
    }
}