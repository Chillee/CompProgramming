#include <bits/stdc++.h>

using namespace std;

vector<int> a;
int total;
void initialize(int n) {
    for (int i = 0; i < n + 2; i++) {
        a.push_back(0);
    }
    total = 0;
}

void add(int k) {
    for (int i = k + 1; i < a.size(); i += (i & -i)) {
        a[i]++;
    }
    total++;
}

int query(int k) {
    int val = 0;
    for (int i = k + 1; i > 0; i -= (i & -i)) {
        assert(k < a.size());
        val += a[i];
    }
    return total - val;
}

int main() {
    freopen("input.txt", "r", stdin);
    int N;
    cin >> N;
    vector<pair<int, pair<int, int>>> data;
    for (int i = 0; i < N; i++) {
        int a, b;
        cin >> a >> b;
        data.push_back({a, {b, i}});
    }

    sort(data.begin(), data.end());

    vector<int> res(data.size(), 0);
    initialize(500000);
    for (int i = data.size() - 1; i >= 0; i--) {
        int cur = i;
        while (cur >= 0 && data[cur].first == data[i].first) {
            cur--;
        }
        for (int j = cur + 1; j <= i; j++) {
            res[data[j].second.second] = query(data[j].second.first);
        }
        for (int j = cur + 1; j <= i; j++) {
            add(data[j].second.first);
        }
        i = cur + 1;
    }
    for (auto i : res) {
        cout << i << ' ';
    }
}