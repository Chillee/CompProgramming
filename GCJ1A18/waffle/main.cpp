#include <bits/stdc++.h>

using namespace std;

const int MAXR = 105;
int T;
char waffle[MAXR][MAXR];
int R, C, H, V;
int totWaf;
int main() {
    // freopen("input.txt", "r", stdin);
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin >> R >> C >> H >> V;
        totWaf = 0;
        for (int i = 0; i < MAXR; i++) {
            for (int j = 0; j < MAXR; j++) {
                waffle[i][j] = 0;
            }
        }
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                cin >> waffle[i][j];
                if (waffle[i][j] == '@') {
                    totWaf++;
                }
            }
        }
        if (totWaf % (H + 1) != 0 || totWaf % (V + 1) != 0) {
            cout << "Case #" << t + 1 << ": IMPOSSIBLE" << endl;
            continue;
        }
        int wafPerRow = totWaf / (H + 1);
        vector<int> rcuts;
        int cnt = 0;
        bool isPossible = true;
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                if (waffle[i][j] == '@')
                    cnt++;
            }
            if (cnt == wafPerRow) {
                rcuts.push_back(i);
                cnt = 0;
            } else if (cnt > wafPerRow) {
                isPossible = false;
                break;
            }
        }
        if (!isPossible) {
            cout << "Case #" << t + 1 << ": IMPOSSIBLE" << endl;
            continue;
        }
        vector<vector<int>> colWaf;
        for (int i = 0; i < rcuts.size(); i++) {
            int curRow = rcuts[i];
            int prevRow = (i == 0) ? 0 : rcuts[i - 1] + 1;
            colWaf.push_back(vector<int>());
            for (int j = 0; j < C; j++) {
                colWaf[i].push_back(0);
                for (int k = prevRow; k <= curRow; k++) {
                    if (waffle[k][j] == '@') {
                        colWaf[i][j]++;
                    }
                }
            }
        }
        if (wafPerRow % (V + 1) != 0) {
            cout << "Case #" << t + 1 << ": IMPOSSIBLE" << endl;
            continue;
        }
        int wafPerCol = wafPerRow / (V + 1);
        vector<int> colcurs;
        for (auto i : colWaf) {
            colcurs.push_back(0);
        }
        bool overallIsPossible = true;
        for (int j = 0; j < C; j++) {
            for (int i = 0; i < colWaf.size(); i++) {
                colcurs[i] += colWaf[i][j];
            }
            // for (auto i : colcurs) {
            //     cout << i << ' ';
            // }
            // cout << endl;
            bool allValid = true;
            for (int i = 0; i < colcurs.size(); i++) {
                if (colcurs[i] != wafPerCol) {
                    allValid = false;
                    break;
                }
            }
            if (allValid) {
                for (int i = 0; i < colcurs.size(); i++) {
                    colcurs[i] = 0;
                }
            }
        }
        for (int i = 0; i < colcurs.size(); i++) {
            if (colcurs[i] != 0) {
                overallIsPossible = false;
                break;
            }
        }
        if (overallIsPossible) {
            cout << "Case #" << t + 1 << ": POSSIBLE" << endl;
        } else {
            cout << "Case #" << t + 1 << ": IMPOSSIBLE" << endl;
        }
    }
}