#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

int N;
string S;
vector<int> houses;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    cin >> S;
    int i = 0;
    int curUsed = 0;
    while (S[i] == 'L') {
        curUsed++, i++;
    }
    curUsed++;
    for (int j = curUsed; j >= 1; j--) {
        houses.push_back(j);
    }
    if (curUsed == 0) {
        houses.push_back(1);
        curUsed++;
    }
    // cout << curUsed << endl;
    while (i < S.size()) {
        i++;
        int cntL = 0;
        while (S[i] == 'L') {
            cntL++;
            i++;
        }
        houses.push_back(curUsed + cntL + 1);
        for (int j = curUsed + cntL; j > curUsed; j--) {
            houses.push_back(j);
        }
        curUsed += cntL + 1;
    }
    for (auto i : houses) {
        cout << i << endl;
    }
}