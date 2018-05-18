#include <bits/stdc++.h>

using namespace std;

string S;
int main() {
    cin >> S;
    int cnt = 0;
    for (auto i : S) {
        if (i == 'o')
            cnt++;
    }
    int linkCnt = S.size() - cnt;
    if (cnt == 0) {
        cout << "YES" << endl;
        return 0;
    }
    if (linkCnt % cnt == 0) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}
