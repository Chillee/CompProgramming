#include <bits/stdc++.h>

using namespace std;

const int MAXM = 1005;
int N;
int arr[MAXM][MAXM];
int main() {
    cin >> N;
    if (N == 2 || N == 3 || N == 5) {
        cout << "Impossible" << endl;
    } else if (N == 1) {
        cout << "Possible" << endl;
        cout << 1 << endl;
        cout << 1 << endl;
    } else {
        cout << "Possible" << endl;
        int M = 0;
        if (N % 2 == 0) {
            M = N / 2;
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < M; j++) {
                    arr[i][j] = 1;
                }
            }
            for (int i = 0; i < M; i++) {
                arr[i][M - 1] = i + M + 2;
                arr[M - 1][i] = i + 2;
            }
        } else if (N % 2 == 1) {
            M = (N - 3) / 2;
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < M; j++) {
                    arr[i][j] = 1;
                }
            }
            for (int i = 0; i < M; i++) {
                arr[i][M - 1] = i + M + 2;
                arr[M - 1][i] = i + 2;
            }
            for (int i = 0; i < M * 2; i++) {
                for (int j = 0; j < M * 2; j++) {
                    if (i < M && j < M) {
                        continue;
                    } else if (i >= M && j < M) {
                        arr[i][j] = 2 * M + 1;
                    } else if (i < M && j >= M) {
                        arr[i][j] = 2 * M + 2;
                    } else {
                        arr[i][j] = 2 * M + 3;
                    }
                }
            }
            M *= 2;
        }
        cout << M << endl;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < M; j++) {
                cout << arr[i][j] << ' ';
            }
            cout << endl;
        }
        // int M = (N - 6) cout << ""
    }
}