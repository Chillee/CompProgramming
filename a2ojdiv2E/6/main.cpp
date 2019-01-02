#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
const ll MAXN = 1e5 + 5;
ll N, M;

pii queens[MAXN];
ll rowScore(pii x) { return x.first; }

ll colScore(pii x) { return x.second; }

ll diag1Score(pii x) { return x.first + x.second; }

ll diag2Score(pii x) { return x.second - x.first; }

map<pii, ll> queenCnt;

function<ll(pii)> scoreFunc;
void process(function<ll(pii)> scoreFunc, function<ll(pii)> secondFunc) {
    sort(queens, queens + M, [&scoreFunc, &secondFunc](pii a, pii b) {
        return scoreFunc(a) * 2 * N + secondFunc(a) > scoreFunc(b) * 2 * N + secondFunc(b);
    });
    ll curScore = scoreFunc(queens[0]);
    vector<pii> curQueens;
    for (ll i = 0; i < M; i++) {
        if (curScore == scoreFunc(queens[i])) {
            curQueens.push_back(queens[i]);
        }
        if (curScore != scoreFunc(queens[i]) || i == M - 1) {
            curScore = scoreFunc(queens[i]);
            if (curQueens.size() != 1) {
                queenCnt[curQueens[0]] += 1;
                queenCnt[*curQueens.rbegin()] += 1;
            }
            for (ll j = 1; j < curQueens.size() - 1; j++) {
                queenCnt[curQueens[j]] += 2;
            }
            curQueens.clear();
            curQueens.push_back(queens[i]);
        }
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for (ll i = 0; i < M; i++) {
        ll a, b;
        cin >> a >> b;
        queens[i] = {a, b};
        queenCnt[queens[i]] = 0;
    }
    process(rowScore, colScore);
    process(colScore, rowScore);
    process(diag1Score, diag2Score);
    process(diag2Score, diag1Score);
    vector<ll> ans(9);
    for (auto i : queenCnt) {
        ans[i.second]++;
    }
    for (auto i : ans) {
        cout << i << ' ';
    }
    cout << endl;
}