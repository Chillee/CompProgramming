#include <bits/stdc++.h>

using namespace std;

int N;
int A[55];
set<int> seen;
int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    vector<int> res;
    for (int i = N - 1; i >= 0; i--) {
        if (seen.count(A[i]) == 0) {
            res.push_back(A[i]);
            seen.insert(A[i]);
        }
    }
    cout << res.size() << endl;
    for (int i = res.size() - 1; i >= 0; i--) {
        cout << res[i] << ' ';
    }
    cout << endl;
}