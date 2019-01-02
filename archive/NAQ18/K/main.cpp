#include <bits/stdc++.h>

// #define endl '\n';
using namespace std;

string T;
string S;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    string result;
    if (T == "E") {
        cin >> S;
        int curCnt = 0;
        char curChr = ' ';
        for (int i = 0; i < S.size(); i++) {
            if (S[i] == curChr) {
                curCnt++;
            } else {
                if (curChr != ' ') {
                    result.push_back(curChr);
                    result.append(to_string(curCnt));
                }
                curCnt = 1;
                curChr = S[i];
            }
        }
        if (curChr != ' ') {
            result.push_back(curChr);
            result.append(to_string(curCnt));
        }
    } else {
        cin >> S;
        int cnt = 0;
        char curChr = 0;
        int i = 0;
        while (i < S.size()) {
            curChr = S[i++];
            cnt = S[i++] - '0';
            for (int j = 0; j < cnt; j++) {
                result.push_back(curChr);
            }
        }
    }
    cout << result << endl;
}