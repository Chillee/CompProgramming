#include <bits/stdc++.h>

using namespace std;

string S;
string vows = "aeiou";
bool isVow(char x) {
    for (auto i : vows)
        if (x == i)
            return true;

    return false;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> S;
    if (!isVow(S[0])) {
        bool allCons = true;
        for (int i = 1; i < S.size(); i++) {
            if (isVow(S[i])) {
                allCons = false;
                break;
            }
        }
        if (allCons) {
            cout << 1 << endl;
        } else {
            cout << 0 << endl;
        }
    } else {
        vector<int> vowPos;
        for (int i = 0; i < S.size(); i++) {
            if (isVow(S[i])) {
                vowPos.push_back(i);
            }
        }
        if (vowPos.size() == 1) {
            cout << S.size() << endl;
            return 0;
        }
        int mid = (vowPos.size() + 1) / 2;
        cout << vowPos[mid] - vowPos[mid - 1] << endl;
    }
}