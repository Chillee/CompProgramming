#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<int> gnomes;
int main() {
    cin >> N >> M;
    int mx = N;
    int t;
    for (int i = 0; i < M; i++) {
        cin >> t;
        gnomes.push_back(t);
    }
    vector<int> sequence;
    for (int i = 0; i <= mx; i++) {
        sequence.push_back(false);
    }
    for (auto i : gnomes) {
        sequence[i] = true;
    }
    int cur = 0;
    vector<int> res;
    for (int i = 0; i < gnomes.size(); i++) {
        int t = gnomes[i];
        vector<int> curels;
        while (t > cur) {
            if (!sequence[t]) {
                curels.push_back(t);
            }
            t--;
        }
        for (int j = curels.size() - 1; j >= 0; j--) {
            res.push_back(curels[j]);
        }
        res.push_back(gnomes[i]);
        cur = max(cur, gnomes[i]);
    }
    vector<int> curels;
    for (int i = mx; i > cur; i--) {
        if (!sequence[i]) {
            curels.push_back(i);
        }
    }
    for (int i = curels.size() - 1; i >= 0; i--) {
        res.push_back(curels[i]);
    }
    for (auto i : res) {
        cout << i << endl;
    }
}