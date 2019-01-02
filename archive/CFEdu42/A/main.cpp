#include <bits/stdc++.h>

using namespace std;

int N;
int A[200005];
int main() {
    cin >> N;
    int tot = 0;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        tot += A[i];
    }
    int cur = 0;
    for (int i = 0; i < N; i++) {
        cur += A[i];
        if (cur >= (tot + 1) / 2) {
            cout << i + 1 << endl;
            return 0;
        }
    }
}