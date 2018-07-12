#include <bits/stdc++.h>

using namespace std;

int N;
int vis[1005];
int main() {
    cin >> N;
    int cur = 0;
    for (int i = 0; i <= N * N; i++) {
        vis[cur % N] = true;
        cur = (cur + i) % N;
    }
    for (int i = 0; i < N; i++) {
        if (!vis[i]) {
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;
}