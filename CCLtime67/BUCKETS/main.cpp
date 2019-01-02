#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;
int N, K;
double prob[MAXN][MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            int t;
            cin >> t;
            prob[i][j] = t;
        }
    }
    double sm = 0;
    for (int i = 0; i < K; i++)
        sm += prob[0][i];
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < K; j++)
            prob[i][j] += prob[i - 1][j] / sm;

        sm = 0;
        for (int j = 0; j < K; j++)
            sm += prob[i][j];
    }
    for (int i = 0; i < K; i++) {
        cout << fixed << setprecision(20) << prob[N - 1][i] / sm << " ";
    }
    cout << endl;
}