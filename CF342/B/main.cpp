#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
string S, P;
int back[MAXN];

void kmpprocess() {
    int j = -1;
    back[0] = -1;
    for (int i = 0; i < P.size(); i++) {
        while (j >= 0 && P[i] != P[j]) {
            j = back[j];
        }
        j++;
        back[i + 1] = j;
    }
}

int kmpsearch(string S) {
    int res = 0;
    int j = 0;
    for (int i = 0; i < S.size(); i++) {
        while (j >= 0 && S[i] != P[j]) {
            j = back[j];
        }
        j++;
        if (j == P.size()) {
            res++;
            j = 0;
        }
    }
    return res;
}
int main() {
    cin >> S >> P;
    kmpprocess();
    cout << kmpsearch(S) << endl;
}