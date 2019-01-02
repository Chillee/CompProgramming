#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e3 + 5;
int P, N, M;
int grid[MAXN][MAXN];
int wLeft[MAXN], wRight[MAXN];
int color[MAXN][MAXN];
struct Dsu {
    int par[MAXN * MAXN], sz[MAXN * MAXN];
    void init(int n) { iota(par, par + n, 0), fill(sz, sz + n, 1); }
    int root(int v) { return v == par[v] ? v : (par[v] = root(par[v])); }

    void merge(int a, int b) {
        if ((a = root(a)) == (b = root(b)))
            return;
        if (sz[a] < sz[b])
            swap(a, b);
        par[b] = a;
        sz[a] += sz[b];
    }
};
bool isValid(int r, int c) { return r >= 0 && c >= 0 && r < N && c < M; }
bool canMerge(int r, int c, int nr, int nc, Dsu &cur) {
    if (isValid(r, c) && isValid(nr, nc) && grid[r][c] && grid[nr][nc] && cur.root(r * M + c) != cur.root(nr * M + nc)) {
        cur.merge(r * M + c, nr * M + nc);
        return true;
    }
    return false;
}
void flood(int r, int c, int clr) {
    if (!isValid(r, c))
        return;
    if (grid[r][c])
        return;
    if (color[r][c] != -1)
        return;
    color[r][c] = clr;
    vector<array<int, 2>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (auto dir : dirs) {
        flood(r + dir[0], c + dir[1], clr);
    }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // cin >> P;
    for (int p = 0; p < 1; p++) {
        for (int i = 0; i < MAXN; i++)
            for (int j = 0; j < MAXN; j++) {
                color[i][j] = -1;
                grid[i][j] = false;
            }
        int K;
        cin >> N >> M;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                char t;
                cin >> t;
                grid[i][j] = (t == '0');
            }
        }
        int numBlack = 0;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++) {
                flood(i, j, i * M + j);
                if (color[i][j] == i * M + j)
                    numBlack++;
            }
        Dsu cur;
        cur.init(N * M);
        int cnt = 0;
        for (int c = 0; c < M; c++) {
            for (int r = 0; r < N; r++) {
                if (grid[r][c]) {
                    cnt++;
                }
                if (canMerge(r, c, r - 1, c, cur)) {
                    cnt--;
                }
                if (canMerge(r, c, r, c - 1, cur)) {
                    cnt--;
                }
            }
            wLeft[c] = cnt;
        }
        cur.init(N * M);
        cnt = 0;
        for (int c = M - 1; c >= 0; c--) {
            for (int r = 0; r < N; r++) {
                if (grid[r][c])
                    cnt++;
                if (canMerge(r, c, r - 1, c, cur))
                    cnt--;
                if (canMerge(r, c, r, c + 1, cur))
                    cnt--;
            }
            wRight[c] = cnt;
        }
        array<int, 2> best = {0, 0};
        for (int c = 0; c < M; c++) {
            int numWhite = c == 0 ? 0 : wLeft[c - 1];
            numWhite += (c == M - 1 ? 0 : wRight[c + 1]);
            unordered_set<int> blackClrs = {-1};
            for (int cc = -1; cc <= 1; cc++) {
                if (c + cc < 0 || c + cc >= M)
                    continue;
                for (int r = 0; r < N; r++) {
                    blackClrs.insert(color[r][c + cc]);
                }
            }
            int cBlack = numBlack - blackClrs.size() + 2;
            if (cBlack + numWhite > best[0] + best[1] || (cBlack + numWhite == best[0] + best[1] && numWhite > best[1])) {
                best = {cBlack, numWhite};
            }
        }
        cout << best[1] << ' ' << best[0] << endl;
    }
}