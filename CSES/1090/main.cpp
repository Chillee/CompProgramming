#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5e5 + 5;
int N, X;
int A[MAXN];
bool used[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> X;
    for (int i = 0; i < N; i++)
        cin >> A[i];
    sort(A, A + N);
    int bidx = N - 1;
    int ans = 0;
    for (int i = 0; i < N; i++) {
        if (used[i])
            continue;
        while (bidx > i) {
            if (A[i] + A[bidx] <= X && !used[bidx])
                break;
            bidx--;
        }
        if (bidx > i) {
            ans++;
            used[bidx] = true, used[i] = true;
        } else {
            ans++;
            used[i] = true;
        }
    }
    cout << ans << endl;
}