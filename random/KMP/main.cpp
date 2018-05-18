#include <bits/stdc++.h>

using namespace std;

#define MAXN 100010

int back[MAXN];
string S, P;

void kmpPreprocess() {
    int j = -1;
    back[0] = -1;
    for (int i = 0; i < P.size(); i++) {
        while (j >= 0 && P[i] != P[j])
            j = back[j];
        j++;
        back[i + 1] = j;
    }
}

vector<int> kmpSearch(string S) {
    vector<int> res;
    int j = 0;
    for (int i = 0; i < S.size(); i++) {
        while (j >= 0 && S[i] != P[j])
            j = back[j];
        j++;
        if (j == P.size()) {
            res.push_back(i - P.size() + 1);
            j = back[j];
        }
    }
    return res;
}

int main() {
    S = "I DO NOT LIKE SEVENTY SEV BUT SEVENTY SEVENTY SEVEN";
    P = "SEVSEB";

    // if the end of line character is read too, uncomment the line below
    // T[n-1] = 0; n--; P[m-1] = 0; m--;

    printf("T = '%s'\n", S.c_str());
    printf("P = '%s'\n", P.c_str());
    printf("\n");

    printf("KMP\n");
    kmpPreprocess();
    for (int i = 0; i < P.size(); i++) {
        cout << back[i] << ' ';
    }
    cout << endl;
    auto res = kmpSearch(S);
    cout << "Matches at: " << endl;
    for (auto i : res) {
        cout << i << endl;
    }

    return 0;
}