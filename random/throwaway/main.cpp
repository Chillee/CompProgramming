#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int mask = bitset<8>("1011").to_ullong();
    for (int i = mask; i > 0; i = (i - 1) & mask) {
        cout << bitset<8>(i).to_string() << endl;
    }
}