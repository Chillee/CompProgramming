#include <bits/stdc++.h>

using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

const int RANDOM = (uint64_t)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
unsigned hash_f(unsigned x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}
unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }
struct chash {
    int operator()(int x) const { return hash_f(x); }
};
const int MAXC = 1e7 + 5;
const int MAXN = 2e5 + 5;
int N;
bool sieve[MAXC];
int comp[MAXC];
vector<int> primes;
vector<int> vals;
gp_hash_table<int, null_type, chash> hprimes;
gp_hash_table<int, int, chash> cnts;
vector<array<int, 2>> answers[MAXN];
int A[MAXN];
void getFactors(int x, int cnt) {
    int pos = comp[x];
    if (x == 1 && cnt == 1) {
        answers[pos].push_back({1, 1});
        return;
    } else if (x == 1 && cnt > 1) {
        cout << "NO" << endl;
        exit(0);
    }
    if (hprimes.find(x) != hprimes.end()) {
        if (cnt > 2) {
            cout << "NO" << endl;
            exit(0);
        }
        answers[pos].push_back({1, x});
        if (cnt > 1)
            answers[pos].push_back({x, 1});
        return;
    }
    vector<int> divs;
    bool isSquare = false;
    int square = 0;
    for (int i = 1; i * i <= x; i++) {
        if (i * i == x) {
            isSquare = true;
            square = i;
        } else if (x % i == 0) {
            divs.push_back(i);
        }
        if (divs.size() * 2 >= cnt) {
            break;
        }
    }
    if (divs.size() * 2 + isSquare < cnt) {
        cout << "NO" << endl;
        exit(0);
    }
    for (int i = 0; i < cnt; i++) {
        if (i == cnt - 1 && isSquare) {
            answers[pos].push_back({square, square});
        } else if (i % 2 == 0) {
            answers[pos].push_back({divs[i / 2], x / divs[i / 2]});
        } else {
            answers[pos].push_back({x / divs[i / 2], divs[i / 2]});
        }
    }
}
int idxs[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int i = 2; i < MAXC; i++) {
        if (sieve[i])
            continue;
        primes.push_back(i);
        for (int j = i; j < MAXC; j += i) {
            sieve[j] = true;
        }
    }
    for (auto i : primes) {
        hprimes.insert(i);
    }
    cin >> N;
    for (int i = 0; i < N; i++) {
        int t;
        cin >> t;
        A[i] = t;
        cnts[t]++;
    }
    int pos = 0;
    for (auto i : cnts) {
        comp[i.first] = pos;
        pos++;
        getFactors(i.first, i.second);
    }
    cout << "YES" << endl;
    for (int i = 0; i < N; i++) {
        auto res = answers[comp[A[i]]][idxs[comp[A[i]]]];
        idxs[comp[A[i]]]++;
        cout << res[0] << ' ' << res[1] << endl;
    }
}