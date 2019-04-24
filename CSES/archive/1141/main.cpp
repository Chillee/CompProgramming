#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;
int N;
int A[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> A[i];
    map<int, int> cur;
    int ans = 0;
    int itr = 0;
    for (int i = 0; i < N; i++) {
        if (cur.find(A[i]) != cur.end() && cur[A[i]] >= itr)
            itr = cur[A[i]] + 1;
        cur[A[i]] = i;
        ans = max(ans, i - itr + 1);
    }
    cout << ans << endl;
}