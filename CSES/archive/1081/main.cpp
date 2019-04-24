#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5e5 + 5;
const int MAXV = 1e6 + 5;
int N;
int A[MAXN];
int cnt[MAXV];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> A[i];
    for (int i = 0; i < N; i++)
        cnt[A[i]]++;
    for (int i = MAXV - 1; i >= 0; i--) {
        int c = 0;
        for (int j = i; j < MAXV; j += i)
            c += cnt[j];
        if (c > 1) {
            cout << i << endl;
            return 0;
        }
    }
}