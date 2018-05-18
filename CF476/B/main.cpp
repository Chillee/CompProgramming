#include <bits/stdc++.h>

using namespace std;

char A[105][105];
int K, N;
bool inBounds(int x, int y) { return x >= 0 && y >= 0 && x < K && y < K; }
int main() {
    cin >> K >> N;
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < K; j++) {
            cin >> A[i][j];
        }
    }
    int mx = -1;
    pair<int, int> mxIdx = {0, 0};
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < K; j++) {
            if (A[i][j] == '#') {
                continue;
            }
            int l = j;
            while (inBounds(i, l) && A[i][l] == '.')
                l--;
            int r = j;
            while (inBounds(i, r) && A[i][r] == '.')
                r++;
            int u = i;
            while (inBounds(u, j) && A[u][j] == '.')
                u--;
            int d = i;
            while (inBounds(d, j) && A[d][j] == '.')
                d++;
            l = abs(l - j);
            r = abs(r - j);
            u = abs(u - i);
            d = abs(d - i);
            int numPlace = 0;
            if (l + r - 1 >= N) {
                l = min(N, l);
                r = min(N, r);
                numPlace += max(l + r - N, 0);
            }
            if (d + u - 1 >= N) {
                u = min(N, u);
                d = min(N, d);
                numPlace += max(d + u - N, 0);
            }
            // cout << i << ' ' << j << ' ' << numPlace << ' ' << l << ' ' << r << ' ' << u << ' ' << d << endl;
            if (numPlace > mx) {
                mxIdx = {i, j};
                mx = numPlace;
            }
        }
    }
    cout << mxIdx.first + 1 << ' ' << mxIdx.second + 1 << endl;
}