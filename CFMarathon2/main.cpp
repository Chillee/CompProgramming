#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
int N, C, S, H, U;
int pattern[MAXN];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> C >> S >> H >> U;
    for (int i = 0; i < N; i++) {
        char c;
        cin >> c;
    }
    for (int i = 0; i < H + S; i++) {
        char c;
        cin >> c;
    }
    for (int i = 0; i < S; i++) {
        cout << 1 << ' ' << 'D' << endl;
    }
}