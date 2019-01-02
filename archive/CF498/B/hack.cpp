#include <bits/stdc++.h>
using namespace std;

#define long long long

template <class T> inline void MIN(T &a, T b) {
    if (a > b)
        a = b;
}
template <class T> inline void MAX(T &a, T b) {
    if (a < b)
        a = b;
}

string s, n;
int ones;

int main() {

    cin >> s;

    for (char c : s) {
        if (c == '1')
            ones++;
        else
            n += c;
    }

    string os = "";
    for (int i = 0; i < ones; i++)
        os += '1';

    for (char c : n) {
        if (c == '2') {
            cout << os;
            os = "";
        }
        cout << c;
    }
    cout << os << endl;
}