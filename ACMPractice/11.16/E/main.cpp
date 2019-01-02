#include <bits/stdc++.h>

using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

typedef array<array<int, 6>, 2> state;
const int RANDOM = (long long)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
unsigned hash_f(unsigned x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}
unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }
struct chash {
    int operator()(state x) const {
        int cur = 1;
        for (int i = 0; i < 6; i++) {
            cur = hash_combine(cur, hash_f(x[0][i]));
        }
        for (int i = 0; i < 6; i++) {
            cur = hash_combine(cur, hash_f(x[1][i]));
        }
        return cur;
    }
};
gp_hash_table<state, double, chash> dp;
int N, M, D;
int tot1, tot2;

double solve(state x) {
    sort(x[0].begin(), x[0].end());
    sort(x[1].begin(), x[1].end());
    int sum1 = 0, sum2 = 0;
    for (int i = 0; i < 6; i++) {
        sum1 += x[0][i];
        sum2 += x[1][i];
    }
    if (tot1 - sum1 + tot2 - sum2 == D) {
        if (sum2 > 0) {
            return 0;
        } else {
            return 1;
        }
    }
    if (dp.find(x) != dp.end()) {
        return dp[x];
    }
    int cnt = 0;
    for (int i = 0; i < 6; i++) {
        if (x[0][i] > 0)
            cnt++;
        if (x[1][i] > 0)
            cnt++;
    }
    double cur = 0;
    for (int i = 0; i < 6; i++) {
        if (x[0][i] > 0) {
            x[0][i]--;
            cur += solve(x);
            x[0][i]++;
        }
        if (x[1][i] > 0) {
            x[1][i]--;
            cur += solve(x);
            x[1][i]++;
        }
    }
    dp[x] = cur / cnt;
    return dp[x];
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M >> D;
    state cur = {};
    for (int i = 0; i < N; i++) {
        cin >> cur[0][i];
        tot1 += cur[0][i];
    }
    for (int i = 0; i < M; i++) {
        cin >> cur[1][i];
        tot2 += cur[1][i];
    }
    if (D >= tot1 + tot2) {
        cout << 1 << endl;
        return 0;
    }
    cout << fixed << setprecision(20) << solve(cur) << endl;
}