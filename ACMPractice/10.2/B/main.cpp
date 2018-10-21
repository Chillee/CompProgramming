#include <bits/stdc++.h>

#define endl '\n';
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

const int RANDOM =
    (uint64_t)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
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

#define map gp_hash_table
const int MAXN = 2 * 1e4 + 5;
const int MAXM = 1e6 + 5;
vector<int> adjlist[MAXN];
int numLeft;
int match[MAXN], dist[MAXN];
const int NIL = 0;
bool bfs() {
    queue<int> Q;
    fill(begin(dist), end(dist), -1);
    for (int i = 1; i <= numLeft; i++) {
        if (match[i] == NIL) {
            dist[i] = 0;
            Q.push(i);
        }
    }
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (auto i : adjlist[u]) {
            if (dist[match[i]] == -1) {
                dist[match[i]] = dist[u] + 1;
                Q.push(match[i]);
            }
        }
    }
    return (dist[NIL] != -1);
}

bool dfs(int u) {
    for (auto v : adjlist[u]) {
        if (match[v] == NIL || (dist[match[v]] == dist[u] + 1 && dfs(match[v]))) {
            match[v] = u;
            match[u] = v;
            return true;
        }
    }
    return false;
}

int hopcroft_karp() {
    int matching = 0;
    fill(begin(match), end(match), NIL);
    while (bfs()) {
        for (int i = 1; i <= numLeft; i++)
            if (match[i] == NIL && dfs(i))
                matching++;
    }
    return matching;
}

int T, N;
bool gender[MAXN];
int A[MAXN];
bool sieve[MAXM];
vector<int> factors[MAXM];
map<int, vector<int>> buckets;
map<int, vector<int>> personalities;
map<int, int> maleMap;
map<int, int> femaleMap;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    fill(sieve, sieve + MAXM, false);
    for (int i = 2; i < MAXM; i++) {
        if (sieve[i])
            continue;
        for (int j = i; j < MAXM; j += i) {
            sieve[j] = true;
            factors[j].push_back(i);
        }
    }
    cin >> T;
    for (int t = 0; t < T; t++) {
        personalities.clear();
        buckets.clear();
        maleMap.clear(), femaleMap.clear();
        for (int i = 0; i < MAXN; i++) {
            adjlist[i].clear();
        }
        cin >> N;
        for (int i = 0; i < N; i++) {
            cin >> A[i];
            personalities[A[i]].push_back(i);
        }
        int numMale = 0;
        for (int i = 0; i < N; i++) {
            char t;
            cin >> t;
            gender[i] = (t == 'M');
            if (gender[i]) {
                numMale++;
                maleMap[i] = numMale;
            } else {
                femaleMap[i] = i - numMale + 1;
            }
        }
        numLeft = numMale;
        for (int i = 0; i < N; i++) {
            for (auto j : factors[A[i]]) {
                buckets[j].push_back(i);
            }
        }
        for (auto i : buckets) {
            vector<int> male;
            vector<int> female;
            for (auto j : i.second) {
                if (gender[j])
                    male.push_back(j);
                else
                    female.push_back(j);
            }
            if (male.size() == 0 || female.size() == 0)
                continue;
            adjlist[maleMap[male[0]]].push_back(femaleMap[female[0]] + numMale);
        }
        int res = hopcroft_karp();
        cout << N - res << endl;
    }
}