#include <bits/stdc++.h>

using namespace std;

string S;
vector<int> zeroBlocks;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> S;
    string ans;
    bool inZero = false;
    int cnt = 0;
    int oneCnt = 0;
    for (int i = 0; i < S.size(); i++) {
        if (!inZero && S[i] == '0') {
            inZero = true;
            cnt++;
        } else if (inZero && S[i] == '0') {
            cnt++;
        }
        if (S[i] == '2') {
            zeroBlocks.push_back(cnt);
            inZero = false;
            cnt = 0;
        } else if (S[i] == '1') {
            oneCnt++;
        }
    }
    if (zeroBlocks.size() == 0) {
        for (int i = 0; i < cnt; i++) {
            cout << "0";
        }
        for (int i = 0; i < oneCnt; i++) {
            cout << "1";
        }
        cout << endl;
        return 0;
    }
    for (int j = 0; j < zeroBlocks[0]; j++) {
        cout << "0";
    }
    for (int i = 0; i < oneCnt; i++) {
        cout << "1";
    }
    cout << "2";
    for (int i = 1; i < zeroBlocks.size(); i++) {
        for (int j = 0; j < zeroBlocks[i]; j++) {
            cout << "0";
        }
        cout << "2";
    }
    for (int i = 0; i < cnt; i++) {
        cout << "0";
    }
    cout << endl;
}