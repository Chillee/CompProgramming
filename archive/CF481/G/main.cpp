#include <bits/stdc++.h>

using namespace std;

char space = '\n';
const int MAXN = 105;
int N, M;
int S[MAXN], D[MAXN], C[MAXN];
int main() {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        cin >> S[i] >> D[i] >> C[i];
        S[i]--;
        D[i]--;
    }
    vector<int> ans;
    for (int d = 0; d < N; d++) {
        bool hasExam = false;
        int examIdx = -1;
        for (int i = 0; i < M; i++) {
            if (D[i] == d) {
                examIdx = i;
                hasExam = true;
                break;
            }
        }
        if (hasExam) {
            if (C[examIdx] > 0) {
                cout << -1 << endl;
                return 0;
            }
            ans.push_back(M + 1);
            continue;
        }
        int minIdx = -1;
        int minDays = 205;
        for (int i = 0; i < M; i++) {
            if (S[i] <= d && D[i] > d && C[i] > 0) {
                if (D[i] - d < minDays) {
                    minIdx = i;
                    minDays = D[i] - d;
                }
            }
        }
        if (minIdx == -1) {
            ans.push_back(0);
        } else {
            ans.push_back(minIdx + 1);
            C[minIdx]--;
        }
    }
    for (auto i : ans) {
        cout << i << ' ';
    }
    cout << endl;
}