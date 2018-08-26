#include <bits/stdc++.h>

using namespace std;

string S;
string revS;
int M;
const int MAXM = 105;
const int MAXP = 1005;
const int MAXN = 1e5 + 5;
const int INF = 1e5;
string words[MAXM];
string rev[MAXM];

int back[MAXP];

void kmpPreprocess(string P) {
    int j = -1;
    back[0] = -1;
    for (int i = 0; i < P.size(); i++) {
        while (j >= 0 && P[i] != P[j])
            j = back[j];
        j++;
        back[i + 1] = j;
    }
}

vector<int> kmpSearch(string S, string P) {
    vector<int> best(MAXP);
    fill(best.begin(), best.end(), INF);
    best[0] = INF;
    int j = 0;
    for (int i = 0; i < S.size(); i++) {
        while (j >= 0 && S[i] != P[j])
            j = back[j];
        j++;
        if (best[j] == INF)
            best[j] = i;
        if (j == P.size())
            j = back[j];
    }
    return best;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> S;
    revS = S;
    reverse(revS.begin(), revS.end());
    cin >> M;
    for (int i = 0; i < M; i++) {
        cin >> words[i];
        rev[i] = words[i];
        reverse(rev[i].begin(), rev[i].end());
    }
    int ans = 0;
    for (int i = 0; i < M; i++) {
        if (words[i].size() == 1)
            continue;
        kmpPreprocess(words[i]);
        auto res = kmpSearch(S, words[i]);
        kmpPreprocess(rev[i]);
        auto revres = kmpSearch(revS, rev[i]);
        // cout << words[i] << endl;
        for (int j = 0; j < words[i].size(); j++) {
            // cout << res[j] << ' ' << revres[words[i].size() - j] << endl;
            if (res[j] + revres[words[i].size() - j] + 2 <= S.size()) {
                ans++;
                break;
            }
        }
        // cout << "----" << endl;
    }
    cout << ans << endl;
}