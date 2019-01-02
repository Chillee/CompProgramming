#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7;

ll N, K;
vector<string> words;
string test;
ll fact[1000005];

const int MAXWORDS = 1e6 + 5;
int seg[MAXWORDS * 2];

ll bin_exp(ll base, ll exp) {
    if (exp == 0)
        return 1;
    return bin_exp(base * base % MOD, exp / 2) * (exp % 2 == 1 ? base : 1) % MOD;
}

ll mod_inv(ll a) { return bin_exp(a, MOD - 2); }

void modify(int p) {
    seg[p += N]++;
    for (; p > 1; p >>= 1) {
        seg[p >> 1] = seg[p] + seg[p ^ 1];
    }
}

ll query(ll l, ll r) {
    ll res = 0;
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            res += seg[l++];
        if (r & 1)
            res += seg[--r];
    }
    return res;
}

int main() {
    fact[0] = 1;
    for (int i = 1; i < 1e6 + 5; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    cin >> N >> K;
    for (ll i = 0; i < N; i++) {
        string s;
        cin >> s;
        words.push_back(s);
    }
    sort(words.begin(), words.end());
    cin >> test;
    vector<ll> cnts;
    vector<int> t;
    t.resize(N);
    for (ll i = 0; i < test.size();) {
        ll pos = 0;
        ll l = 0;
        ll r = words.size();
        while (true) {
            pos = 0;
            if (l == r - 1) {
                break;
            }
            ll m = (l + r) / 2;
            string s = words[m];

            while (true) {
                if (pos == s.size()) {
                    l = m;
                    r = l + 1;
                    break;
                }
                if (s[pos] < test[pos + i]) {
                    l = m;
                    break;
                } else if (s[pos] > test[pos + i]) {
                    r = m;
                    break;
                } else {
                    pos += 1;
                }
            }
        }
        cnts.push_back(l);
        t[l] = 1;
        i += words[l].size();
    }

    ll res = 0;
    set<ll> prev;
    for (ll i = 0; i < K; i++) {
        ll num_frags_before = query(0, cnts[i]);
        ll fac = ((cnts[i] - num_frags_before) * fact[N - 1 - i]) % MOD;
        ll inv = mod_inv(fact[N - K]);
        modify(cnts[i]);
        res = (res + (fac * inv)) % MOD;
    }

    cout << (res + 1) % MOD << endl;
}