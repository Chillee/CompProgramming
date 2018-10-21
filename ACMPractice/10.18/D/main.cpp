#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

typedef long double ld;
double const EPS = 1e-6;
const int MAXN = 1e5 + 5;
int N, W;
vector<int> ordering;
int cost[MAXN];
ld rat[MAXN];
bool cmp(int a, int b) {
    if (abs(rat[a] - 1) < EPS) {
        return false;
    } else if (abs(rat[b] - 1) < EPS) {
        return true;
    }
    ld score1 = cost[a] / (1.0 - rat[a]);
    ld score2 = cost[b] / (1.0 - rat[b]);
    return score1 < score2;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> W;
    for (int i = 0; i < N; i++) {
        cin >> cost[i] >> rat[i];
        ordering.push_back(i);
    }
    sort(ordering.begin(), ordering.end(), cmp);
    ld ans = 0;
    ld curW = W;
    for (auto i : ordering) {
        ans += curW * cost[i];
        curW *= rat[i];
    }
    cout << fixed << setprecision(20) << ans << endl;
}