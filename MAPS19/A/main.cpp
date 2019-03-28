#include <bits/stdc++.h>

using namespace std;

const int MAXN = 55;
int F, B;
vector<array<int, 2>> vals;
int Fs[MAXN], Bs[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> F >> B;
    for (int i = 0; i < F; i++)
        cin >> Fs[i];
    for (int i = 0; i < B; i++)
        cin >> Bs[i];
    for (int i = 0; i < F; i++) {
        for (int j = 0; j < B; j++) {
            // vals.push_back({});
        }
    }
    sort(vals.begin(), vals.end());
    // for ()
}