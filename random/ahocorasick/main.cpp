#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
const int MAXCHAR = 26;

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

vector<Vertex> trie(1);

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

int go(int v, char ch);

int get_link(int v) {
    if (trie[v].link == -1) {
        if (v == 0 || trie[v].p == 0)
            trie[v].link = 0;
        else
            trie[v].link = go(get_link(trie[v].p), trie[v].pch);
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

string S;
vector<string> M;
vector<int> results[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    string S = "aaabbbbaaabababab";
    M = {"abbbbaaabab", "aaabbbbaaaba", "baaabab", "abbbbaaababa"};
    for (int i = 0; i < M.size(); i++) {
        add_string(M[i], i);
    }
    for (int i = 1; i < trie.size(); i++) //
        get_link(i);                      //

    int v = 0;
    for (int i = 0; i < S.size(); i++) {
        get_link(v);
        v = go(v, S[i]);
        int cur = v;
        while (cur != -1 && trie[cur].leaf != -1) {
            results[trie[cur].leaf].push_back(i);
            get_link(cur);
            cur = trie[cur].leaflink;
        }
    }

    for (int i = 0; i < M.size(); i++) {
        cout << "Found instances for " << M[i] << ": ";
        for (auto j : results[i]) {
            cout << j << ' ';
        }
        cout << endl;
    }
}