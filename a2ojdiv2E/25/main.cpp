#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
int N;
bool grundy[MAXN][100];
int curSum[MAXN];
int curGrundy[MAXN];
int mex(int x) {
    for (int i = 0; i < 100; i++) {
        if (!grundy[x][i])
            return i;
    }
    return 0;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    curGrundy[1] = 0;
    curSum[1] = 1;
    int lowSum = 1;
    int ans = MAXN;
    for (int i = 2; i <= N; i++) {
        int curMex = mex(i);
        for (int j = lowSum; j <= i; j++) {
            curSum[j] += i;
            curGrundy[j] ^= curMex;
            if (curSum[j] > N) {
                lowSum++;
            } else {
                if (j == i)
                    continue;
                if (curSum[j] == N && curGrundy[j] == 0) {
                    ans = min(i - j + 1, ans);
                }
                grundy[curSum[j]][curGrundy[j]] = true;
            }
        }
    }
    if (ans >= MAXN) {
        cout << -1 << endl;
        return 0;
    }
    cout << ans << endl;
}