#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
const int MAXCHAR = 26;
int N;

struct Vertex {
    int next[MAXCHAR];
    bool leaf = false;
    Vertex() { fill(begin(next), end(next), -1); }
};
vector<Vertex> trie(1);
void add_string(string const &s) {
    int v = 0;
    for (char ch : s) {
        int c = ch - 'a';
        if (trie[v].next[c] == -1) {
            trie[v].next[c] = trie.size();
            trie.emplace_back(v, ch);
        }
        v = trie[v].next[c];
    }
    trie[v].leaf = true;
}

multiset<int> dp(int pos, int depth) {
    multiset<int> cur;
    for (int i = 0; i < 26; i++) {
        if (trie[pos].next[i] != -1) {
            auto t = dp(trie[pos].next[i], depth + 1);
            if (t.size() > cur.size())
                swap(t, cur);
            for (auto j : t) {
                cur.insert(j);
            }
        }
    }
    if (pos == 0) {
    } else if (trie[pos].leaf) {
        cur.insert(depth);
    } else {
        auto mxEl = cur.rbegin();
        cur.erase(cur.find(*mxEl));
        cur.insert(depth);
    }
    return cur;
}

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        add_string(s);
    }
    auto res = dp(0, 0);
    int ans = 0;
    for (auto i : res) {
        ans += i;
    }
    cout << ans << endl;
}