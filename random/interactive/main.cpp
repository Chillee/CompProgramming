#include <bits/stdc++.h>

using namespace std;

void binSearch(int l, int r) {
    int mid = (l + r) / 2;
    cout << mid << endl;
    if (l == r - 1) {
        cout << "! " << l << endl;
        return;
    }
    string res;
    cin >> res;
    if (res == "<") {
        binSearch(l, mid);
    } else {
        binSearch(mid, r);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    binSearch(0, 1000001);
}