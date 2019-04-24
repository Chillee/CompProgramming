#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
const int MAXN = 1005;
struct Trie {
    const static int MAXCHAR = 26;
    struct Vertex {
        int nxt[MAXCHAR];
        bool leaf = false;
        int cnt = 0;
        Vertex() { fill(begin(nxt), end(nxt), -1); }
        int &operator[](int x) { return nxt[x]; }
    };
    Trie() : trie(1) {}
    vector<Vertex> trie;
    Vertex &operator[](int x) { return trie[x]; }
    void add_string(string const &s) {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'A';
            if (trie[v][c] == -1) {
                trie[v][c] = trie.size();
                trie.emplace_back();
            }
            v = trie[v][c];
            trie[v].cnt++;
        }
        trie[v].leaf = true;
    }
};
int T, N;
string words[MAXN];
int cnt(Trie &trie, int cur) {
    // cout << cur << ' ' << trie.trie[cur].cnt << endl;
    if (trie[cur].cnt == 2 && cur != 0)
        return 2;
    else if (trie[cur].cnt < 2 && cur != 0)
        return 0;
    int ans = 0;
    for (int i = 0; i < 26; i++) {
        if (trie[cur].nxt[i] == -1)
            continue;
        ans += cnt(trie, trie[cur][i]);
    }
    if (cur == 0)
        return ans;

    return ans + (trie[cur].cnt - ans >= 2) * 2;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin >> N;
        for (int i = 0; i < N; i++)
            cin >> words[i];
        for (int i = 0; i < N; i++)
            reverse(words[i].begin(), words[i].end());
        Trie trie;
        for (int i = 0; i < N; i++)
            trie.add_string(words[i]);
        cout << "Case #" << t + 1 << ": " << cnt(trie, 0) << endl;
    }
}