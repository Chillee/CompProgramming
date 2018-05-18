#include <bits/stdc++.h>

using namespace std;

int N, K;
int main() {
    cin >> N >> K;
    for (int i = 0; i < K; i++) {
        if (N % 10 == 0) {
            N /= 10;
        } else {
            N--;
        }
    }
    cout << N << endl;
}