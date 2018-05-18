#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
const int MAXCHAR = 26;

struct Vertex {
    int next[MAXCHAR];
    int leaf = -1;
    int p = -1;
    char pch;
    int link = -1;
    int leaflink = -1;
    int go[MAXCHAR];

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

int getleaf(int i) {
    if (trie[i].leaflink != -1) {
        return trie[i].leaflink;
    }
    int nxt = get_link(i);
    if (nxt > 0) {
        if (trie[nxt].leaf != -1) {
            trie[i].leaflink = nxt;
        } else {
            trie[i].leaflink = getleaf(nxt);
        }
        return trie[i].leaflink;
    }
    return 0;
}

string S;
vector<string> M;
vector<int> results[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    string S = "abbb abbababbbab";
    M = {"b", "ab", "bb", "abb", "bbb", "a", "abbb"};
    for (int i = 0; i < M.size(); i++) {
        add_string(M[i], i);
    }

    int v = 0;
    for (int i = 0; i < S.size(); i++) {
        v = go(v, S[i]);
        int cur = v;
        while (getleaf(cur) > 0) {
            cur = getleaf(cur);
            results[trie[cur].leaf].push_back(i);
        }
        if (trie[v].leaf != -1) {
            results[trie[v].leaf].push_back(i);
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