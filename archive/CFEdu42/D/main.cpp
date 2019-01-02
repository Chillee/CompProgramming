#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

ll N;
ll A[150005];
map<ll, priority_queue<ll>> cnts;

int main() {
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(0);
    cin >> N;
    for (ll i = 0; i < N; i++) {
        cin >> A[i];
        if (cnts.count(A[i]) == 0) {
            cnts[A[i]] = priority_queue<ll>();
        }
        cnts[A[i]].push(i);
    }
    vector<pii> leftovers;
    while (!cnts.empty()) {
        ll mn = (*cnts.begin()).first;
        if (cnts[mn].size() < 2) {
            leftovers.push_back(pii(cnts[mn].top(), mn));
            cnts.erase(cnts.begin());
            continue;
        }
        auto t = (*cnts.begin()).second;
        vector<int> positions;
        while (!t.empty()) {
            positions.push_back(std::move(const_cast<ll &>(t.top())));
            t.pop();
        }
        reverse(positions.begin(), positions.end());
        for (ll i = 0; i < positions.size(); i += 2) {
            if (i + 1 == (ll)positions.size()) {
                break;
            }
            if (cnts.count(2 * mn) == 0) {
                cnts[2 * mn] = priority_queue<ll>();
            }
            cnts[2 * mn].push(positions[i + 1]);
        }
        if (positions.size() % 2 == 1) {
            leftovers.push_back(pii(positions[positions.size() - 1], mn));
        }
        cnts.erase(cnts.begin());
    }
    sort(leftovers.begin(), leftovers.end());
    cout << leftovers.size() << endl;
    for (auto i : leftovers) {
        cout << i.second << ' ';
    }
    cout << endl;
}