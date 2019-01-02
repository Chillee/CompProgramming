#include <bits/stdc++.h>

using namespace std;

const int MAX = 1e9;
int M, N;
vector<bool> truths;
void binSearch(int l, int r, int idx) {
    int mid = (l + r) / 2;
    cout << mid << endl;
    fflush(stdout);
    int t;
    cin >> t;
    if (t == 0) {
        exit(0);
        return;
    } else if ((t == -1) ^ truths[idx % truths.size()]) {
        binSearch(l, mid, idx + 1);
    } else {
        binSearch(mid, r, idx + 1);
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> M >> N;
    for (int i = 0; i < N; i++) {
        cout << M << endl;
        fflush(stdout);
        int res;
        cin >> res;
        if (res == -1) {
            truths.push_back(false);
        } else if (res == 1) {
            truths.push_back(true);
        } else if (res == 0) {
            exit(0);
            return 0;
        }
    }
    binSearch(0, M + 1, 0);
}