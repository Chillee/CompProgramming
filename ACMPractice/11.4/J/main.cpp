#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
string S;
unordered_map<int, int> cnts;
unordered_set<int> p[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> S;
    int N = S.length();
    for (int i = 1; i < N; i++) {
        cnts[__gcd(i, N)]++;
    }
    vector<int> divs;
    for (int i = 1; i < N; i++) {
        if (cnts[i])
            divs.push_back(i);
    }
    for (int i = 0; i < N; i++) {
        if (S[i] == 'P') {
            for (int j : divs) {
                p[j].insert(i % j);
            }
        }
    }
    int sum = 0;
    for (int i : divs) {
        if (p[i].size() < i) {
            sum += cnts[i];
        }
    }
    cout << sum << endl;
}