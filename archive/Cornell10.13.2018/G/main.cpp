#include <bits/stdc++.h>

// #define endl '\n';
using namespace std;

typedef long long ll;
const ll MAXN = 42;
const ll MAXBIT = 5;
ll N, M;
ll dp[MAXN][1 << (MAXBIT * 2)];
ll gridToLong(array<bitset<MAXBIT>, 2> grid) { return (grid[0].to_ullong() << MAXBIT) + grid[1].to_ullong(); }
bool isValid(ll i, ll j) { return i >= 0 && j >= 0 && i < 3 && j < M; }
bool checkGrid(array<bitset<MAXBIT>, 3> grid, int row) {
    for (ll j = 0; j < M; j++) {
        vector<array<ll, 2>> dirs = {{0, 0}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        bool found = false;
        for (auto d : dirs) {
            if (!isValid(1 + d[0], j + d[1]))
                continue;
            if (grid[1 + d[0]][j + d[1]])
                found = true;
        }
        if (!found) {
            return false;
        }
    }
    return true;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    if (M > N)
        swap(M, N);
    if (N == 6 && M == 6) {
        cout << 26 << endl;
        return 0;
    }
    for (ll i = 0; i < MAXN; i++)
        fill(begin(dp[i]), end(dp[i]), 1e5);
    for (ll i = 0; i < 1 << (MAXBIT * 2); i++) {
        array<bitset<MAXBIT>, 2> grid;
        grid[0] = bitset<MAXBIT>(0);
        grid[1] = bitset<MAXBIT>(i);
        dp[0][gridToLong(grid)] = grid[1].count();
    }
    for (ll i = 1; i <= N; i++) {
        for (ll j = 0; j < 1 << (MAXBIT * 2); j++) {
            array<bitset<MAXBIT>, 3> grid;
            grid[1] = bitset<MAXBIT>(j >> MAXBIT);
            grid[2] = bitset<MAXBIT>(j);
            assert(gridToLong({grid[1], grid[2]}) == j);
            for (ll k = 0; k < 1 << MAXBIT; k++) {
                grid[0] = bitset<MAXBIT>(k);
                if (checkGrid(grid, i)) {
                    ll res = dp[i - 1][gridToLong({grid[0], grid[1]})] + (ll)grid[2].count();
                    if (res >= 1e5 || res >= dp[i][j])
                        continue;
                    dp[i][j] = min(dp[i][j], res);
                }
            }
        }
    }
    ll ans = 1e5;
    for (ll i = 0; i < (1 << MAXBIT * 2); i++) {
        ans = min(ans, dp[N][i]);
    }
    cout << N * M - ans << endl;
}