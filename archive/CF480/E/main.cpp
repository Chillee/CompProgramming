#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 5;
const int MAXHEIGHT = 25;

int K, N;

vector<int> adjlist[MAXN];
int par[MAXN][MAXHEIGHT];
bool added[MAXN];

int root(int cur) {
    for (auto i : adjlist[cur]) {
        if (par[i][0] != -1)
            continue;
        par[i][0] = cur;
        root(i);
    }
}
int countBinLift(int cur) {
    if (added[cur])
        return 0;
    if (!added[cur] && added[par[cur][0]])
        return 1;
    for (int i = 0; i < MAXHEIGHT; i++) {
        if (!added[par[cur][i]] && added[par[cur][i + 1]]) {
            return (1 << i) + countBinLift(par[cur][i]);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> K;
    // scanf("%d %d", &N, &K);
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        // scanf("%d %d", &a, &b);

        a--;
        b--;
        adjlist[a].push_back(b);
        adjlist[b].push_back(a);
    }
    for (int i = 0; i < N; i++) {
        par[i][0] = -1;
    }
    for (int i = 0; i < MAXHEIGHT; i++) {
        par[N - 1][i] = N - 1;
    }
    root(N - 1);
    for (int i = 1; i < MAXHEIGHT; i++) {
        for (int j = 0; j < N; j++) {
            par[j][i] = par[par[j][i - 1]][i - 1];
        }
    }
    added[N - 1] = true;
    int total = 1;
    for (int i = N - 2; i >= 0; i--) {
        int res = countBinLift(i);

        if (N - (total + res) >= K) {
            total += res;
            int cur = i;
            while (!added[cur]) {
                added[cur] = true;
                cur = par[cur][0];
            }
        }
    }
    for (int i = 0; i < N; i++) {
        if (!added[i]) {
            // printf("%d ", i + 1);
            cout << i + 1 << ' ';
        }
    }
}