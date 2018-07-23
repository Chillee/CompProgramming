#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
bool sieve[MAXN];
vector<int> primes;
int T, A, B, C;
vector<int> getFactors(int n) {
    vector<int> res;
    for (int i = 1; i * i <= n; i++) {
        if (i * i == n) {
            res.push_back(i);
        } else if (n % i == 0) {
            res.push_back(i);
            res.push_back(n / i);
        }
    }
    return res;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // fill(sieve, sieve + MAXN, true);
    // for (int i = 2; i < MAXN; i++) {
    //     if (sieve[i]) {
    //         primes.push_back(i);
    //         for (int j = i; j < MAXN; j += i) {
    //             sieve[j] = false;
    //         }
    //     }
    // }
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin >> A >> B >> C;
        vector<int> cur = {A, B, C};
        sort(cur.begin(), cur.end());
        vector<int> factors;
        A = cur[0];
        B = cur[1];
        C = cur[2];
        vector<int> afactors = getFactors(A);
        vector<int> bfactors = getFactors(B);
        vector<int> cfactors = getFactors(C);
        // sort(factors.begin(), factors.end());
        // cout << factors.size() << endl;
        int ans = 0;
        set<tuple<int, int, int>> answers;
        for (int i = 0; i < afactors.size(); i++) {
            for (int j = 0; j < bfactors.size(); j++) {
                for (int k = 0; k < cfactors.size(); k++) {
                    vector<int> curAns = {afactors[i], bfactors[j], cfactors[k]};
                    sort(curAns.begin(), curAns.end());
                    answers.insert({curAns[0], curAns[1], curAns[2]});
                }
            }
        }
        // for (auto i : answers) {
        //     cout << get<0>(i) << ' ' << get<1>(i) << ' ' << get<2>(i) << endl;
        // }
        cout << answers.size() << endl;

        // vector<int> cfactors;
        // int curVal = factors[0];
        // int curCnt = 0;
        // for (auto i : factors) {
        //     // cout << i << ' ' << curVal << ' ' << curCnt << endl;
        //     if (i == curVal) {
        //         curCnt++;
        //     } else {
        //         cfactors.push_back(curCnt);
        //         curVal = i;
        //         curCnt = 1;
        //     }
        // }
        // cfactors.push_back(curCnt);
        // int ans = 0;
        // int totSum = cfactors.size();
        // for (int i = 0; i < cfactors.size(); i++) {
        //     if ()
        //     for(int j=i; j<cfactors.size(); j++) {

        //     }
        // }
    }
}