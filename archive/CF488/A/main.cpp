#include <bits/stdc++.h>

using namespace std;

int N, M;
bool hasFingerprint[10];
int seq[15];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> seq[i];
    }
    for (int i = 0; i < M; i++) {
        int t;
        cin >> t;
        hasFingerprint[t] = true;
    }
    vector<int> ans;
    for (int i = 0; i < N; i++) {
        if (hasFingerprint[seq[i]]) {
            ans.push_back(seq[i]);
        }
    }
    for (auto i : ans) {
        cout << i << ' ';
    }
    cout << endl;
}