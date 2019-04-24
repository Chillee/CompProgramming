#include <bits/stdc++.h>

using namespace std;

string S;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> S;
    int mxCnt = 0;
    char prv = '$';
    int curCnt = 0;
    for (auto i : S) {
        if (i == prv) {
            curCnt++;
        } else {
            prv = i;
            curCnt = 1;
        }
        mxCnt = max(mxCnt, curCnt);
    }
    cout << mxCnt << endl;
}