#include <bits/stdc++.h>

#define endl '\n';
using namespace std;

vector<int> suffix_array(string s) {
    int n = s.size();
    vector<int> sa(n), rank(n);
    for (int i = 0; i < n; i++)
        rank[i] = s[i], sa[i] = i;
    for (int k = 0; k < n; k ? k *= 2 : k = 1) {
        stable_sort(sa.begin(), sa.end(), [&](int i, int j) {
            if (rank[i] == rank[j])
                return rank[(i + k) % n] < rank[(j + k) % n];
            return rank[i] < rank[j];
        });
        vector<int> nrank(n);
        int r = 0;
        for (int i = 1; i < n; i++) {
            if (rank[sa[i]] != rank[sa[i - 1]])
                r++;
            else if (rank[(sa[i] + k) % n] != rank[(sa[i - 1] + k) % n])
                r++;
            nrank[sa[i]] = r;
        }
        rank = nrank;
    }
    return sa;
}

string vowels = "aeiou";
bool isVowel(char x) { return vowels.find(x) != -1; }
void findSubstrings(string s) {
    int lastConsonant = 0;
    for (int i = s.size() - 1; i >= 0; i--) {
        if (!isVowel(s[i])) {
            lastConsonant = i;
            break;
        }
    }
    auto suffixarray = suffix_array(s);
    string fst;
    for (auto i : suffixarray) {
        if (i >= lastConsonant || !isVowel(s[i]))
            continue;
        int cPos;
        for (int j = i; j < s.size(); j++) {
            if (!isVowel(s[j])) {
                cPos = j;
                break;
            }
        }
        fst = s.substr(i, cPos - i + 1);
        break;
    }
    reverse(suffixarray.begin(), suffixarray.end());
    string lst;
    for (auto i : suffixarray) {
        if (i >= lastConsonant || !isVowel(s[i]))
            continue;
        int cPos;
        for (int j = s.size() - 1; j >= i; j--) {
            if (!isVowel(s[j])) {
                cPos = j;
                break;
            }
        }
        lst = s.substr(i, cPos - i + 1);
        break;
    }
    cout << fst << endl;
    cout << lst << endl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    findSubstrings("aba");
    // auto res = suffix_array_construction("edcba");
    // for (auto i : res) {
    //     cout << i << endl;
    // }
}