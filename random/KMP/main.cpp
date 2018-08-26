#include <bits/stdc++.h>

using namespace std;

#define MAXN 100010

int back[MAXN];
string S, P;

void kmpPreprocess(string P) {
    int cur = -1;
    back[0] = cur;
    for (int i = 1; i < P.size(); i++) {
    }
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