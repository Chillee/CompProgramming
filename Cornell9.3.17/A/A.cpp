#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> A;
int main() {
    cin >> N;
    for (int i = 0; i < 2 * N; i++) {
        int t;
        cin >> t;
        A.push_back(t);
    }
    sort(A.begin(), A.end());
    if (A[A.size() / 2] == A[A.size() / 2 - 1]) {
        cout << "NO" << endl;
        return 0;
    }

    cout << "YES" << endl;
}