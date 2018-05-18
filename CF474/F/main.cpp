#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int MAXN = 1e5 + 5;
int N, M;
int A[MAXN], B[MAXN], W[MAXN];
map<int, int> dp[MAXN];

int main() {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        cin >> A[i] >> B[i] >> W[i];
    }
    int res = 0;
    for (int i = 0; i < M; i++) {
        auto mxVal = dp[A[i]].lower_bound(W[i]);
        int val = -1;
        if (mxVal == dp[A[i]].begin()) {
            val = 1;
        } else {
            val = prev(mxVal)->second + 1;
        }
        while (true) {
            auto ub = dp[B[i]].lower_bound(W[i]);
            if (ub != dp[B[i]].end() && ub->second <= val) {
                dp[B[i]].erase(ub);
            } else {
                break;
            }
        }
        auto lb = dp[B[i]].lower_bound(W[i]);
        if (lb != dp[B[i]].begin() && prev(lb)->second >= val) {
            continue;
        } else {
            dp[B[i]][W[i]] = val;
        }
        res = max(dp[B[i]][W[i]], res);
    }
    cout << res << endl;
}