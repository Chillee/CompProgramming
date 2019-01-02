#include <bits/stdc++.h>

using namespace std;

int N, M;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
    }
    for (int i = 0; i < N; i++) {
        if (i % 2 == 0) {
            cout << "0";
        } else {
            cout << "1";
        }
    }
    cout << endl;
}