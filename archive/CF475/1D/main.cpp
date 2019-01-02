#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
const int MAXCHAR = 26;

struct AhoCorasick {
    struct Vertex {
        int next[MAXCHAR], go[MAXCHAR];
        int leaf = -1;
        int p = -1;
        char pch;
        int link = -1, leaflink = -1;

        Vertex(int p = -1, char ch = '$') : p(p), pch(ch) {
            fill(begin(next), end(next), -1);
            fill(begin(go), end(go), -1);
        }
    };
    vector<Vertex> trie;
    vector<int> results[MAXN];
    AhoCorasick() : trie(1) {}

    void add_string(string const &s, int idx) {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (trie[v].next[c] == -1) {
                trie[v].next[c] = trie.size();
                trie.emplace_back(v, ch);
            }
            v = trie[v].next[c];
        }
        trie[v].leaf = idx;
    }

    int get_link(int v) {
        if (trie[v].link == -1) {
            if (v == 0 || trie[v].p == 0)
                trie[v].link = 0;
            else
                trie[v].link = go(get_link(trie[v].p), trie[v].pch);
            get_link(trie[v].link);
            trie[v].leaflink = (trie[trie[v].link].leaf != -1) ? trie[v].link : trie[trie[v].link].leaflink;
        }
        return trie[v].link;
    }

    int go(int v, char ch) {
        int c = ch - 'a';
        if (trie[v].go[c] == -1) {
            if (trie[v].next[c] != -1)
                trie[v].go[c] = trie[v].next[c];
            else
                trie[v].go[c] = v == 0 ? 0 : go(get_link(v), ch);
        }
        return trie[v].go[c];
    }

    void findString(string s) {
        int v = 0;
        for (int i = 0; i < s.size(); i++) {
            v = go(v, s[i]);
            get_link(v);
            int cur = trie[v].leaf == -1 ? trie[v].leaflink : v;
            while (cur != -1) {
                results[trie[cur].leaf].push_back(i);
                cur = trie[cur].leaflink;
            }
        }
    }
};

string S;
int N;
int K[MAXN];
string M[MAXN];

AhoCorasick aho;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> S;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> K[i];
        cin >> M[i];
        aho.add_string(M[i], i);
    }
    aho.findString(S);

    for (int i = 0; i < N; i++) {
        int minLength = 1 << 30;
        for (int j = K[i]; j <= aho.results[i].size(); j++) {
            minLength = min(minLength, aho.results[i][j - 1] - aho.results[i][j - K[i]]);
        }
        if (minLength == 1 << 30) {
            cout << -1 << endl;
        } else {
            cout << minLength + M[i].size() << endl;
        }
    }
}