#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;
int N;
int A[MAXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    int ans = 0;
    int cnt = 1;
    int curElem = A[0];
    for (int i = 1; i < N; i++) {
        if (A[i] != curElem) {
            curElem = A[i];
            ans += cnt / 2;
            cnt = 1;
        } else {
            cnt++;
        }
    }
    ans += cnt / 2;
    cout << ans << endl;
}