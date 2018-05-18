#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;
const int MAXSUM = MAXN * 255;
int T;
int N;
int P;
int W[MAXN];
int H[MAXN];

int main() {
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin >> N >> P;
        for (int i = 0; i < N; i++) {
            cin >> W[i] >> H[i];
        }
        double minCut = 2 * min(W[0], H[0]);
        double maxCut = 2 * sqrtl(W[0] * W[0] + H[0] * H[0]);
        double curP = 2 * (W[0] + H[0]) * N;
        double curBuffer = 0;

        for (int i = 0; i < N; i++) {
            if (curP + minCut <= P) {
                curP += minCut;
                curBuffer += maxCut - minCut;
            } else {
                break;
            }
        }
        if (curP != P) {
            curP = min(curP + curBuffer, (double)P);
        }
        printf("Case #%d: %.9lf\n", t + 1, curP);
    }
}