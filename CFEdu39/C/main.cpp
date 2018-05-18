#include <bits/stdc++.h>

using namespace std;

string s;
int main() {
    cin >> s;
    int cur = 'a';
    int startidx = 0;
    int endidx = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] <= cur && cur <= 'z') {
            s[i] = cur;
            cur += 1;
        }
    }
    if (cur <= 'z') {
        cout << -1 << endl;
        return 0;
    }
    cout << s << endl;
}