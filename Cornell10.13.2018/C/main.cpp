#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

const int MAXN = 1e4 + 5;
int K;
bool adjMat[MAXN][MAXN];
int start = 0, end = 1;
int curNode = 2;
int pathLen = -1;
void addpath(int a, int b) {
    if (a == b)
        return;
    adjMat[a][b] = true;
    adjMat[b][a] = true;
}
void addpaths(int num) {
    addpath(0, curNode);
    curNode++;
    if (num > 0) {
        addpath(curNode - 1, curNode);
        addpath(curNode - 1, curNode + 1);
        curNode += 2;
        for (int i = 1; i < num; i++) {
            addpath(curNode, curNode - 1);
            addpath(curNode, curNode - 2);
            addpath(curNode + 1, curNode - 1);
            addpath(curNode + 1, curNode - 2);
            curNode += 2;
        }
        addpath(curNode - 1, curNode);
        addpath(curNode - 2, curNode);
        curNode++;
    }
    if (num == 0) {
        addpath(curNode - 1, 2 + (30 - num - 1));
    } else {
        addpath(curNode - 1, 2 + (30 - num - 2));
    }
    // for (int i = num; i < pathLen; i++) {
    //     addpath(curNode, curNode - 1);
    //     curNode++;
    // }
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> K;
    for (int i = 0; i < 30; i++) {
        addpath(curNode, curNode - 1);
        curNode++;
    }
    // addpath(curNode - 1, 0);
    for (int i = 30; i >= 0; i--) {
        if ((K & (1 << i)) == 0)
            continue;
        if (pathLen == -1)
            pathLen = i + 1;
        addpaths(i);
    }
    cout << curNode << endl;
    // int cnt = 0;
    // for (int i = 0; i < curNode; i++) {
    //     cnt += (adjMat[i][0]);
    // }
    // for (int i = 0; i < curNode; i++) {
    //     for (int j = 0; j < curNode; j++) {
    //         cout << (adjMat[i][j] ? 'Y' : 'N');
    //     }
    //     cout << endl;
    // }
}