#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

const int MAXN = 1e3 + 5;
int N, M;
int A[MAXN], B[MAXN];
bool isPossible[MAXN];
int center = -1;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    fill(isPossible, isPossible + MAXN, true);
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        cin >> A[i] >> B[i];
        A[i]--, B[i]--;
        isPossible[A[i]] = false;
        isPossible[B[i]] = false;
    }
    for (int i = 0; i < N; i++) {
        if (isPossible[i]) {
            center = i;
            break;
        }
    }
    if (center == -1) {
        assert(false);
    }
    cout << N - 1 << endl;
    for (int i = 0; i < N; i++) {
        if (i == center)
            continue;
        cout << (i + 1) << ' ' << (center + 1) << endl;
    }
}