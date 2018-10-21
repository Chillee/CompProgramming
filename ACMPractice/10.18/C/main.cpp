#include <bits/stdc++.h>

// #define endl '\n';
using namespace std;

int N, S;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> S;
    string tt;
    getline(cin, tt);
    for (int i = 0; i < N; i++) {
        string line;
        getline(cin, line);
        for (auto i : line) {
            if (i >= 'a' && i <= 'z') {
                char t = ((i - 'a' - (S % 26) + 26) % 26) + 'a';
                cout << t;
            } else if (i >= 'A' && i <= 'Z') {
                char t = ((i - 'A' - (S % 26) + 26) % 26) + 'A';
                cout << t;
            } else {
                char t = i;
                cout << t;
            }
        }
        cout << endl;
    }
}