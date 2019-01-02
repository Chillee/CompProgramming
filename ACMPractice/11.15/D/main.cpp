#include <bits/stdc++.h>

using namespace std;

string S;
vector<string> outs;
int findmin(int start) {
    int lo = 1000, loind = -1;
    for (int i = start; i < S.size(); i++) {
        if (S[i] < lo) {
            lo = S[i];
            loind = i;
        }
    }
    return loind;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> S;
    int next = 0;
    while (next < S.size()) {
        int i = findmin(next);
        // cout << i << ' ' << next << endl;
        if (i != next) {
            outs.push_back(to_string(i + 1) + " " + to_string(next + 1));
            char temp = S[next];
            S[next] = S[i];
            S[i] = temp;
        }
        next++;
    }
    reverse(outs.begin(), outs.end());
    for (auto i : outs) {
        cout << i << endl;
    }
}