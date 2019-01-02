#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2005;
int N;
int A[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> A[i];
    cout << N + 1 << endl;
    int curSum = 0;
    for (int i = N - 1; i >= 0; i--) {
        int add = (i - (A[i] + curSum) % N) + N;
        curSum += add;
        cout << 1 << ' ' << i + 1 << ' ' << add << endl;
    }
    cout << 2 << ' ' << N << ' ' << N << endl;
}