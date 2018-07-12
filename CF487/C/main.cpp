#include <bits/stdc++.h>

using namespace std;

int SIZE = 50;
int counts[4];
int mapping[4] = {'A', 'B', 'C', 'D'};
char grid[55][55];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> counts[0] >> counts[1] >> counts[2] >> counts[3];
    int i = 0;
    int char1;
    int char2;

    char1 = 0;
    char2 = 1;
    counts[char1]--;
    for (; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = mapping[char1];
        }
        if (counts[char2] == 1) {
            break;
        }
        if (i % 2 == 0) {
            for (int j = 0; j < SIZE; j++) {
                grid[i][j] = mapping[char1];
            }
        } else {
            for (int j = 0; j < SIZE; j++) {
                if (j % 2 == 0 && counts[char2] > 1) {
                    counts[char2]--;
                    grid[i][j] = mapping[char2];
                } else {
                    grid[i][j] = mapping[char1];
                }
            }
        }
    }
    char1 = 2;
    char2 = 3;
    counts[char1]--;
    i++;
    for (; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = mapping[char1];
        }
        if (counts[char2] == 1) {
            break;
        }
        if (i % 2 == 0) {
            for (int j = 0; j < SIZE; j++) {
                grid[i][j] = mapping[char1];
            }
        } else {
            for (int j = 0; j < SIZE; j++) {
                if (j % 2 == 0 && counts[char2] > 1) {
                    counts[char2]--;
                    grid[i][j] = mapping[char2];
                } else {
                    grid[i][j] = mapping[char1];
                }
            }
        }
    }
    char1 = 1;
    char2 = 0;
    counts[char1]--;
    i++;
    for (; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = mapping[char1];
        }
        if (counts[char2] == 0) {
            break;
        }
        if (i % 2 == 0) {
            for (int j = 0; j < SIZE; j++) {
                grid[i][j] = mapping[char1];
            }
        } else {
            for (int j = 0; j < SIZE; j++) {
                if (j % 2 == 0 && counts[char2] > 0) {
                    counts[char2]--;
                    grid[i][j] = mapping[char2];
                } else {
                    grid[i][j] = mapping[char1];
                }
            }
        }
    }
    char1 = 3;
    char2 = 2;
    counts[char1]--;
    i++;
    for (; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = mapping[char1];
        }
        if (counts[char2] == 0) {
            break;
        }
        if (i % 2 == 0) {
            for (int j = 0; j < SIZE; j++) {
                grid[i][j] = mapping[char1];
            }
        } else {
            for (int j = 0; j < SIZE; j++) {
                if (j % 2 == 0 && counts[char2] > 0) {
                    counts[char2]--;
                    grid[i][j] = mapping[char2];
                } else {
                    grid[i][j] = mapping[char1];
                }
            }
        }
    }
    cout << i + 1 << ' ' << 50 << endl;
    for (int j = 0; j <= i; j++) {
        for (int k = 0; k < SIZE; k++) {
            cout << grid[j][k];
        }
        cout << endl;
    }
}