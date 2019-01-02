#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
string S;
int numZ, numO, numQ;
set<string> res;
vector<char> vS;
int leftZ = MAXN;
int rightO = -1;
int leftQ = MAXN;
int rightQ = -1;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> S;
    for (auto i : S) {
        if (i == '0') {
            numZ++;
        }
        if (i == '1')
            numO++;
        if (i == '?')
            numQ++;
    }
    for (int i = 0; i < S.size(); i++) {
        if (S[i] == '0') {
            leftZ = min(leftZ, i);
        }
        if (S[i] == '1') {
            rightO = max(rightO, i);
        }
        if (S[i] == '?') {
            leftQ = min(leftQ, i);
            rightQ = max(rightQ, i);
        }
    }
    if (numO + numQ >= numZ + 2) {
        res.insert("11");
    }
    if (numO + 1 <= numZ + numQ) {
        res.insert("00");
    }
    for (auto i : S) {
        vS.push_back(i);
    }
    vector<char> curS = vS;
    int cur0 = numZ;
    int cur1 = numO;
    int ridx = curS.size() - 1;
    int lidx = 0;
    while (true) {
        while (ridx >= 0 && cur0 > cur1) {
            if (curS[ridx] == '?') {
                curS[ridx] = '1';
                cur1++;
            }
            ridx--;
        }
        while (lidx < curS.size() && cur1 > cur0) {
            if (curS[lidx] == '?') {
                curS[lidx] = '0';
                cur0++;
            }
            lidx++;
        }
        if (lidx >= curS.size() && ridx < 0) {
            break;
        }
        while (ridx >= 0 && curS[ridx] != '?') {
            ridx--;
        }
        if (ridx >= 0) {
            curS[ridx] = '1';
            cur1++;
        }
        while (lidx < curS.size() && curS[lidx] != '?') {
            lidx++;
        }
        if (lidx < curS.size()) {
            curS[lidx] = '0';
            cur0++;
        }
    }
    int left0, right1;
    for (int i = 0; i < curS.size(); i++) {
        if (curS[i] == '0') {
            left0 = i;
            break;
        }
    }
    for (int i = curS.size() - 1; i >= 0; i--) {
        if (curS[i] == '1') {
            right1 = i;
            break;
        }
    }
    if (curS[curS.size() - 1] == '1' && cur0 <= cur1 && cur1 <= cur0 + 1) {
        res.insert("01");
    }
    curS = vS;
    cur0 = numZ;
    cur1 = numO;
    ridx = curS.size() - 1;
    lidx = 0;
    while (true) {
        while (ridx >= 0 && cur0 < cur1) {
            if (curS[ridx] == '?') {
                curS[ridx] = '0';
                cur0++;
            }
            ridx--;
        }
        while (lidx < curS.size() && cur1 <= cur0) {
            if (curS[lidx] == '?') {
                curS[lidx] = '1';
                cur1++;
            }
            lidx++;
        }
        if (lidx >= curS.size() && ridx < 0) {
            break;
        }
        while (ridx >= 0 && curS[ridx] != '?') {
            ridx--;
        }
        if (ridx >= 0) {
            curS[ridx] = '0';
            cur0++;
        }
        while (lidx < curS.size() && curS[lidx] != '?') {
            lidx++;
        }
        if (lidx < curS.size()) {
            curS[lidx] = '1';
            cur1++;
        }
    }
    left0, right1;
    for (int i = 0; i < curS.size(); i++) {
        if (curS[i] == '0') {
            left0 = i;
            break;
        }
    }
    for (int i = curS.size() - 1; i >= 0; i--) {
        if (curS[i] == '1') {
            right1 = i;
            break;
        }
    }
    if (curS[curS.size() - 1] == '0' && cur0 >= cur1 - 1 && cur1 >= cur0) {
        res.insert("10");
    }
    for (auto i : res) {
        cout << i << endl;
    }
}