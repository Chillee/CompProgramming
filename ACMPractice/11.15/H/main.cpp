#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e3 + 5;
int B, P;
int K;
int D[MAXN];
int minD[MAXN];
int cur[MAXN];
bool isValid(int x) {
    if (x != K - 1) {
        if (cur[x + 1] != P - 1 && D[cur[x + 1]] - D[cur[x] + 1] < max(minD[x + 1], minD[x])) {
            return false;
        }
    }
    if (x != 0) {
        if (D[cur[x] + 1] - D[cur[x - 1]] > B) {
            // cout << D[cur[x] + 1] << endl;
            // cout << "FAILED" << endl;
            return false;
        }
    }
    return true;
    // if (cur[x] != P - 1) {
    //     if ()
    // }
    // if (D[cur[x]+1] < )
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> B >> P;
    for (int i = 0; i < P; i++)
        cin >> D[i];
    cin >> K;
    for (int i = 0; i < K; i++) {
        cin >> minD[i] >> cur[i];
        cur[i]--;
    }
    int ptr = K - 1;
    vector<int> ans;
    while (true) {
        if (ptr == 0 && cur[0] == P - 1) {
            break;
        } else if (cur[ptr] == P - 1) {
            ptr--;
            continue;
        } else if (isValid(ptr)) {
            cur[ptr]++;
            ans.push_back(ptr);
            ptr++;
            continue;
        } else if (ptr == 0) {
            cout << "impossible" << endl;
            return 0;
        } else {
            ptr--;
        }
    }
    for (auto i : ans) {
        cout << i + 1 << ' ';
    }
    cout << endl;
}