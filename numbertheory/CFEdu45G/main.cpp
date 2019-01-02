#include <bits/stdc++.h>

using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

typedef long long ll;
const int RANDOM = (long long)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
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
const int MAXN = 2e5 + 5;
int N;
int A[MAXN];
vector<ll> divs;
ll g[MAXN];
bool vis[MAXN];
vector<int> adj[MAXN];
int count(int cur, int d) {
    if (vis[cur])
        return 0;
    if (A[cur] % d) {
        return 0;
    }
    vis[cur] = true;
    int sm = 1;
    for (auto i : adj[cur]) {
        sm += count(i, d);
    }
    return sm;
}
ll mobius[MAXN];
bool sieve[MAXN];
vector<int> primes;
void calc() {
    mobius[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        if (!sieve[i]) {
            primes.push_back(i);
            mobius[i] = -1;
        }
        for (int j = 0; j < primes.size() && i * primes[j] < MAXN; j++) {
            sieve[i * primes[j]] = true;
            if (i % primes[j] == 0) {
                mobius[i * primes[j]] = 0;
                break;
            }
            mobius[i * primes[j]] = mobius[i] * -1;
        }
    }
}
ll ans[MAXN];
vector<int> exists[MAXN];
vector<int> starts[MAXN];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    calc();
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        exists[A[i]].push_back(i);
    }
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 1; i < MAXN; i++) {
        bool found = false;
        for (int j = i; j < MAXN; j += i) {
            if (exists[j].size() > 0) {
                found = true;
                for (auto k : exists[j]) {
                    starts[i].push_back(k);
                }
            }
        }
        if (found) {
            divs.push_back(i);
        }
    }
    for (auto d : divs) {
        ll sm = 0;
        for (auto i : starts[d]) {
            vis[i] = false;
        }
        for (auto i : starts[d]) {
            ll res = count(i, d);
            sm += res * (res + 1) / 2;
        }
        g[d] = sm;
    }
    for (int i = 0; i < divs.size(); i++) {
        ll cur = 0;
        for (int j = divs[i]; j < MAXN; j += divs[i]) {
            cur += g[j] * mobius[j / divs[i]];
        }
        ans[divs[i]] = cur;
    }
    for (int i = 0; i < MAXN; i++) {
        if (ans[i] != 0)
            cout << i << ' ' << ans[i] << endl;
    }
}