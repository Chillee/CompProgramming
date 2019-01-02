#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e3 + 5;
int N, L, X[MAXN], B[MAXN];
double dp[MAXN];
int prv[MAXN];
bool f(double ratio) {
    fill(begin(dp), end(dp), 1e18);
    dp[0] = 0;
    for (int i = 1; i < N; i++) {
        double ep = ratio * B[i];
        for (int j = 0; j < i; j++) {
            double res = dp[j] + sqrt(abs(X[i] - X[j] - L)) - ep;
            if (res < dp[i]) {
                dp[i] = res;
                prv[i] = j;
            }
        }
    }
    // cout << ratio << endl;
    // for (int i = 0; i < N; i++)
    //     cout << dp[i] << " ";
    // cout << endl;
    return dp[N - 1] <= 0;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> L;
    N++;
    for (int i = 1; i < N; i++) {
        cin >> X[i] >> B[i];
    }
    double l = 0, r = 1e12;
    for (int iter = 0; iter < 100; iter++) {
        double m = (l + r) / 2;
        if (f(m)) {
            r = m;
        } else {
            l = m;
        }
    }
    vector<int> res;
    int cur = N - 1;
    while (cur != 0) {
        res.push_back(cur);
        cur = prv[cur];
    }
    reverse(res.begin(), res.end());
    for (auto i : res)
        cout << i << ' ';
    cout << endl;
}