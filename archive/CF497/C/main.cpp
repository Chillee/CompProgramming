#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
int N;
int A[MAXN];
vector<int> vals;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        vals.push_back(A[i]);
    }
    sort(vals.begin(), vals.end());
    int ans = 0;
    int curIdx = 0;
    for (int i = 0; i < N; i++) {
        while (curIdx < N && vals[curIdx] <= vals[i]) {
            curIdx++;
        }
        if (curIdx == N) {
            break;
        }
        ans++;
        curIdx++;
    }
    cout << ans << endl;
}