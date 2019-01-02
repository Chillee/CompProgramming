#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5;
int N, K;
int A[MAXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    int cur = K;
    for (int i = 0; i < N; i++) {
        cur = __gcd(A[i], cur);
    }
    cout << K / cur << endl;
    for (int i = 0; i < K; i += cur) {
        cout << i << ' ';
    }
    cout << endl;
}