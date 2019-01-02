#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
int P, K, N;
int F[MAXN], G[MAXN], H[MAXN];
int Fc[MAXN][3], Gc[MAXN][3], Hc[MAXN][3];
// 0: 1x1, 1:1x2, 2: L
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int t = 0; t < 1; t++) {
        cin >> N;
        fill(begin(F), end(F), 0);
        fill(begin(G), end(G), 0);
        fill(begin(H), end(H), 0);
        G[0] = 1;
        for (int i = 1; i <= N; i++) {
            F[i] = F[i - 1] + G[i - 1] + H[i - 1];
            Fc[i][0] = 2 * F[i - 1] + 2 * G[i - 1] + 1 * H[i - 1];
            Fc[i][0] += Fc[i - 1][0] + Gc[i - 1][0] + Hc[i - 1][0];
            Fc[i][1] = Fc[i - 1][1] + Gc[i - 1][1] + Hc[i - 1][1];
            Fc[i][2] = Fc[i - 1][2] + Gc[i - 1][2] + Hc[i - 1][2];

            G[i] = G[i - 1] + F[i - 1];
            Gc[i][0] = Gc[i - 1][0] + Fc[i - 1][0];
            Gc[i][1] = G[i - 1] + F[i - 1];
            Gc[i][1] += Gc[i - 1][1] + Fc[i - 1][1];
            Gc[i][2] = Gc[i - 1][2] + Fc[i - 1][2];

            H[i] = 4 * F[i - 1] + 4 * G[i - 1] + H[i - 1];
            Hc[i][0] = 4 * Fc[i - 1][0] + 4 * Gc[i - 1][0] + Hc[i - 1][0];
            Hc[i][0] += 2 * F[i - 1] + 2 * G[i - 1];
            Hc[i][1] = 4 * Fc[i - 1][1] + 4 * Gc[i - 1][1] + Hc[i - 1][1];
            Hc[i][1] += 2 * F[i - 1] + 2 * G[i - 1] + 1 * H[i - 1];
            Hc[i][2] = 4 * Fc[i - 1][2] + 4 * Gc[i - 1][2] + Hc[i - 1][2];
            Hc[i][2] += 2 * F[i - 1] + 2 * G[i - 1];

            if (i > 1) {
                G[i] += 3 * F[i - 2] + 3 * G[i - 2] + H[i - 2];
                Gc[i][0] += 3 * Fc[i - 2][0] + 3 * Gc[i - 2][0] + Hc[i - 2][0];
                Gc[i][0] += 2 * F[i - 2] + 2 * G[i - 2];
                Gc[i][1] += 3 * Fc[i - 2][1] + 3 * Gc[i - 2][1] + Hc[i - 2][1];
                Gc[i][1] += 2 * F[i - 2] + 2 * G[i - 2];
                Gc[i][2] += 3 * Fc[i - 2][2] + 3 * Gc[i - 2][2] + Hc[i - 2][2];
                Gc[i][2] += 2 * F[i - 2] + 2 * G[i - 2] + H[i - 2];
            }
        }
        cout << F[N] + G[N] << ' ' << Fc[N][0] + Gc[N][0] << ' ' << Fc[N][1] + Gc[N][1] << ' ' << Fc[N][2] + Gc[N][2] << endl;
    }
}