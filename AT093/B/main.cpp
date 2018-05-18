#include <bits/stdc++.h>

using namespace std;

char arr[100][100];

int A, B;
int main() {
    cin >> A >> B;
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 100; j++) {
            arr[i][j] = '.';
        }
    }
    for (int i = 50; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            arr[i][j] = '#';
        }
    }
    for (int i = 0; i < B - 1; i++) {
        arr[(i / 50) * 2][(i % 50) * 2] = '#';
    }
    for (int i = 0; i < A - 1; i++) {
        arr[99 - (i / 50) * 2][(i % 50) * 2] = '.';
    }
    cout << 100 << ' ' << 100 << endl;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            cout << arr[i][j];
        }
        cout << endl;
    }
}