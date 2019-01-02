#include <bits/stdc++.h>

using namespace std;

string S;
vector<char> vowels = {'a', 'o', 'u', 'i', 'e'};
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> S;
    for (int i = 0; i < S.size() - 1; i++) {
        if (S[i] == 'n') {
            continue;
        } else if (find(vowels.begin(), vowels.end(), S[i]) != vowels.end()) {
            continue;
        } else {
            if (find(vowels.begin(), vowels.end(), S[i + 1]) == vowels.end()) {
                cout << "NO" << endl;
                return 0;
            }
        }
    }
    if (find(vowels.begin(), vowels.end(), S[S.size() - 1]) == vowels.end() && S[S.size() - 1] != 'n') {
        cout << "NO" << endl;
        return 0;
    }
    cout << "YES" << endl;
}