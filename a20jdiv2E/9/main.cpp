#include <bits/stdc++.h>

using namespace std;

set<int> valid;
unordered_map<int, int> cnt;
const int MAXN = 1e5 + 5;
int N, K;
int A[MAXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < K; i++) {
        if (cnt[A[i]] == 1) {
            valid.erase(A[i]);
        }
        cnt[A[i]]++;
        if (cnt[A[i]] == 1) {
            valid.insert(A[i]);
        }
    }
    if (valid.size() == 0) {
        cout << "Nothing" << endl;
    } else {
        cout << *valid.rbegin() << endl;
    }
    for (int i = 1; i < N - K + 1; i++) {
        if (cnt[A[i - 1]] == 1) {
            valid.erase(A[i - 1]);
        }
        cnt[A[i - 1]]--;
        if (cnt[A[i - 1]] == 1) {
            valid.insert(A[i - 1]);
        }
        if (cnt[A[i + K - 1]] == 1) {
            valid.erase(A[i + K - 1]);
        }
        cnt[A[i + K - 1]]++;
        if (cnt[A[i + K - 1]] == 1) {
            valid.insert(A[i + K - 1]);
        }
        if (valid.size() == 0) {
            cout << "Nothing" << endl;
        } else {
            cout << *valid.rbegin() << endl;
        }
    }
}