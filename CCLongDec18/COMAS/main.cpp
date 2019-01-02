#include <bits/stdc++.h>

using namespace std;

int cnt = 0;
array<vector<int>, 2> query(vector<int> x) {
    cnt++;
    sort(x.begin(), x.end());
    // vector<int> t = {x[0], x[1], x[4]}, t2 = {x[2], x[3]};
    // return {t2, t};
    cout << "? ";
    for (auto i : x) {
        cout << i << ' ';
    }
    cout << endl;
    int a, b;
    cin >> a >> b;
    vector<int> left;
    for (auto i : x) {
        if (i != a && i != b)
            left.push_back(i);
    }
    vector<int> rm = {a, b};
    return {rm, left};
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // cin>>N;
    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        int N;
        cin >> N;

        vector<int> nums;
        vector<int> removed;
        vector<int> erased[105];
        for (int i = 1; i <= N; i++) {
            nums.push_back(i);
        }
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();

        // swap(nums[2], nums[N - 1]);
        shuffle(nums.begin(), nums.end(), default_random_engine(seed));
        vector<int> nextnums;
        while (nums.size() > 3) {
            // cout << "Nums:5";
            // for (auto i : nums) {
            //     cout << i << ' ';
            // }
            // cout << endl;
            for (int i = 0; i < nums.size(); i += 5) {
                if (i + 5 > nums.size() && nums.size() > 5) {
                    for (int j = i; j < nums.size(); j++) {
                        nextnums.push_back(nums[j]);
                    }
                    break;
                }
                vector<int> ask;
                for (int j = i; j < i + 5; j++) {
                    if (j >= nums.size()) {
                        ask.push_back(removed[j - nums.size()]);
                    } else {
                        ask.push_back(nums[j]);
                    }
                }
                auto res = query(ask);
                for (auto j : res[0]) {
                    removed.push_back(j);
                    removed.push_back(j);
                }
                for (auto j : res[1]) {
                    nextnums.push_back(j);
                }
                for (auto j : res[1]) {
                    erased[j].push_back(res[0][0]);
                    // for (auto k : res[0])
                    //     erased[j].push_back(k);
                }
            }
            for (auto i : removed) {
                if (find(nextnums.begin(), nextnums.end(), i) != nextnums.end()) {
                    nextnums.erase(find(nextnums.begin(), nextnums.end(), i));
                }
            }
            // unique(removed.begin(), removed.end());
            nums = nextnums;
            nextnums.clear();
        }
        // for (auto i : nums) {
        //     cout << i << ' ';
        // }
        // cout << endl;
        int cnts[101];
        set<int> elems;
        fill(begin(cnts), end(cnts), 0);
        for (auto i : nums) {
            // cout << i << endl;
            sort(erased[i].begin(), erased[i].end());
            for (auto j : erased[i]) {
                elems.insert(j);
                cnts[j]++;
                // cout << j << endl;
            }
        }
        vector<int> cands = nums;
        shuffle(cands.begin(), cands.end(), default_random_engine(seed));
        vector<int> midcands;
        vector<int> other;
        for (int i = 1; i <= 100; i++) {
            if (cnts[i] >= 2) {
                midcands.push_back(i);
            }
        }
        for (int i = 1; i <= 100; i++) {
            if (i != cands[0] && i != cands[1] && i != cands[2] && cnts[i] < 2 && midcands.size() != 3 && midcands.size() != 9) {
                midcands.push_back(i);
            }
        }
        // cout << "midcands: ";
        // for (auto j : midcands) {
        //     cout << j << ' ';
        // }
        // cout << endl;
        while (midcands.size() > 1) {
            vector<int> nxt = midcands;
            for (int i = 0; i < midcands.size(); i += 3) {
                if (i + 3 > midcands.size()) {
                    continue;
                }

                vector<int> ask = {cands[0], cands[1]};
                for (int j = i; j < i + 3; j++) {
                    ask.push_back(midcands[j]);
                }
                auto res = query(ask);
                for (auto j : res[0]) {
                    auto t = find(nxt.begin(), nxt.end(), j);
                    if (t != nxt.end()) {
                        nxt.erase(t);
                        other.push_back(j);
                    }
                }
            }
            midcands = nxt;
        }
        vector<int> ask = {cands[0], cands[2], midcands[0]};
        for (int i = 0; i < 2; i++) {
            ask.push_back(other[i]);
        }
        // cout << "ask: ";
        // for (auto i : ask)
        //     cout << i << ' ';
        // cout << endl;
        auto res = query(ask);
        // cout << "cands: " << cands[0] << " " << cands[1] << endl;
        // cout << "mid: " << midcands[0] << endl;
        if (res[0][0] == midcands[0]) {
            cout << "! " << cands[1] << endl;
        } else if (res[0][1] == midcands[0]) {
            cout << "! " << cands[2] << endl;
        } else {
            cout << "! " << cands[0] << endl;
        }
        // for (auto i : res[0]) {
        //     cout << i << ' ';
        // }
        // cout << endl;
    }
}