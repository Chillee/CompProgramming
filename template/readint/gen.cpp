#include <bits/stdc++.h>

using namespace std;

signed main(int argc, char *argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int cnt = 0;
    if (argc > 1) {
        cnt = atoi(argv[1]);
    }
    cout << cnt << endl;
    for (int i = 0; i < cnt; i++) {
        cout << rand() << '\n';
    }
}