#include <bits/stdc++.h>

using namespace std;

int N, B;
int A[105];
int preSum[105];
vector<int> cuts;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> B;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    if (A[0] % 2 == 0) {
        preSum[0] = 1;
    } else {
        preSum[0] = -1;
    }
    for (int i = 1; i < N - 1; i++) {
        preSum[i] = preSum[i - 1];
        if (A[i] % 2 == 0) {
            preSum[i]++;
        } else {
            preSum[i]--;
        }
        if (preSum[i] == 0) {
            cuts.push_back(abs(A[i] - A[i + 1]));
        }
    }
    sort(cuts.begin(), cuts.end());
    int ans = 0;
    for (auto i : cuts) {
        if (B - i < 0) {
            break;
        }
        ans++;
        B -= i;
    }
    cout << ans << endl;
}