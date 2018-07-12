#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2005;
int T;
string A;
bool test(string A, string B) {
    int i = 1, j = 1;
    while (true) {
        if (i > A.size()) {
            return true;
        } else if (j > B.size()) {
            return false;
        } else if (A[i - 1] == B[j - 1]) {
            i++, j++;
        } else if (i == 1) {
            j++;
        } else {
            i = 1;
        }
    }
    return true;
}
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cin >> A;
        string result;
        for (int i = 1; i < A.size(); i++) {
            if (A[i] == A[0]) {
                result = A.substr(0, i) + A;
                break;
            }
        }
        if (test(A, result)) {
            cout << "Case #" << t << ": Impossible" << endl;
            continue;
        } else if (result == "") {
            cout << "Case #" << t << ": Impossible" << endl;
            continue;
        } else {
            cout << "Case #" << t << ": " << result << endl;
        }
    }
}