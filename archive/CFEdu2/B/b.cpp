#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<int> A, B;
int main() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        int t;
        cin >> t;
        A.push_back(t);
    }
    for (int j = 0; j < M; j++) {
        int t;
        cin >> t;
        B.push_back(t);
    }
    sort(A.begin(), A.end());
    for (auto i : B) {
        cout << upper_bound(A.begin(), A.end(), i) - A.begin() << ' ';
    }
}