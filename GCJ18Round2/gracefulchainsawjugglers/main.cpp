#include <bits/stdc++.h>

using namespace std;

const int MAXN=505;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    vector<vector<int>> dp(MAXN, vector<int>(MAXN, 0));
    vector<vector<int>> prev(MAXN, vector<int>(MAXN, 0));
    for (int i=0; i<35; i++) {
        for (int j=0; j<35; j++) {
            for(int k=0; k<=500-i; k++) {
                for(int l=0;l<=500-j; l++) {
                    dp[i+k][j+l] = max(prev[i+k][j+l], prev[k][l] + 1);
                }
            }
            for (int k=0; k<MAXN; k++) {
                for (int l =0; l<MAXN; l++) {
                    prev[k][l] = dp[k][l];
                }
            }
        }
    }

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int a, b;
        cin >> a >> b;
        cout << "Case #" << t << ": " << dp[a][b] - 1 << endl;
    }
    return 0;
}