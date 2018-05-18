#include <bits/stdc++.h>

using namespace std;

int N;
typedef pair<int, int> pii;

vector<pii> shows;
int tv1, tv2;
int main() {
    tv1 = -1; tv2 = -1;
    cin >> N;
    for (int i = 0; i < N; i++) {
        int a, b;
        cin >> a >> b;
        shows.push_back(pii(a, b));
    }
    sort(shows.begin(), shows.end());
    for (auto i : shows) {
        if (i.first > tv1) {
            tv1 = i.second;
        } else if (i.first > tv2) {
            tv2 = i.second;
        } else {
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;
}