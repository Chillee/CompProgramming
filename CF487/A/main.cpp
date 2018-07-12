#include <bits/stdc++.h>

using namespace std;

string S;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> S;
    if (S.size() <= 2) {
        cout << "NO" << endl;
        return 0;
    }
    for (int i = 0; i < S.size() - 2; i++) {
        vector<int> chars = {S[i], S[i + 1], S[i + 2]};
        sort(chars.begin(), chars.end());
        if (chars[0] == 'A' && chars[1] == 'B' && chars[2] == 'C') {
            cout << "Yes" << endl;
            return 0;
        }
    }
    cout << "No" << endl;
}