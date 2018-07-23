#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
int N, M;
vector<int> adjlist[MAXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    if (M < N - 1) {
        cout << "Impossible" << endl;
        return 0;
    }
    for (int i = 2; i <= N; i++) {
        adjlist[1].push_back(i);
        M--;
    }
    int curIdx = 2;
    int curIdxIdx = 3;
    for (int i = 0; i < M; i++) {
        for (;; curIdxIdx++) {
            if (curIdxIdx == N + 1) {
                curIdx++;
                curIdxIdx = curIdx + 1;
            }
            if (curIdx >= N) {
                cout << "Impossible" << endl;
                return 0;
            }
            if (__gcd(curIdxIdx, curIdx) == 1) {
                adjlist[curIdx].push_back(curIdxIdx);
                curIdxIdx++;
                break;
            }
        }
    }
    cout << "Possible" << endl;
    for (int i = 1; i <= N; i++) {
        for (auto j : adjlist[i]) {
            cout << i << ' ' << j << endl;
        }
    }
}