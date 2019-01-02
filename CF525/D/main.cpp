#include <bits/stdc++.h>

using namespace std;

const int MAXB = 30;
int query(bitset<MAXB> a, bitset<MAXB> b) {
    cout << "? " << a.to_ulong() << ' ' << b.to_ulong() << endl;
    int t;
    cin >> t;
    return t;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    bitset<MAXB> curA(0), curB(0);
    int aBigger = 0;
    bool needUpdate = true;
    vector<int> ans;
    for (int i = MAXB - 1; i >= 0; i--) {
        if (needUpdate)
            aBigger = query(curA, curB);
        if (aBigger == 0) {
            for (; i >= 0; i--) {
                ans.push_back(0);
            }
            break;
        }
        curA.flip(i);
        curB.flip(i);
        int res = query(curA, curB);
        if (res != aBigger) {
            if (aBigger == 1) {
                ans.push_back(1);
            } else {
                ans.push_back(-1);
            }
            curA.flip(i);
            needUpdate = true;
        } else {
            ans.push_back(0);
            needUpdate = false;
        }
    }
    bitset<MAXB> finalA(0), finalB(0);
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++) {
        if (ans[i] == 1) {
            finalA[i] = 1;
            finalB[i] = 0;
        } else if (ans[i] == -1) {
            finalA[i] = 0;
            finalB[i] = 1;
        }
    }
    for (int i = ans.size() - 1; i >= 0; i--) {
        if (ans[i] == 0) {
            finalB.flip(i);
            int res = query(finalA, finalB);
            if (res == 1) {
                finalA[i] = 1;
                finalB[i] = 1;
            } else {
                finalA[i] = 0;
                finalB[i] = 0;
            }
        }
    }
    cout << "! " << finalA.to_ulong() << ' ' << finalB.to_ulong() << endl;
}