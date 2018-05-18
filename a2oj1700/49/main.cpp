#include <bits/stdc++.h>

using namespace std;

int K;
vector<pair<int, int>> edgelist;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> K;
    if (K == 1) {
        cout << "YES" << endl;
        cout << 2 << ' ' << 1 << endl;
        cout << 1 << ' ' << 2 << endl;
        return 0;
    } else if (K % 2 == 0) {
        cout << "NO" << endl;
        return 0;
    }
    int numNodes = K + 2;
    for (int i = 2; i < numNodes - 1; i++) {
        edgelist.push_back({0, i});
        edgelist.push_back({1, i});
    }
    edgelist.push_back({1, 0});
    for (int i = 2; i < numNodes - 1; i++) {
        edgelist.push_back({i, numNodes - 1});
    }
    for (int i = 2; i < numNodes - 1; i++) {
        for (int j = i + 1; j < numNodes - 1; j++) {
            if (i % 2 == 0 && j == i + 1)
                continue;
            edgelist.push_back({i, j});
        }
    }
    cout << "YES" << endl;
    cout << numNodes * 2 << ' ' << edgelist.size() * 2 + 1 << endl;
    for (auto i : edgelist) {
        cout << i.first + 1 << ' ' << i.second + 1 << endl;
        cout << i.first + numNodes + 1 << ' ' << i.second + numNodes + 1 << endl;
    }
    cout << numNodes << ' ' << 2 * numNodes << endl;
}