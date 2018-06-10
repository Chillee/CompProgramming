#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;
int N, W;
int bear[MAXN];
int elephant[MAXN];

int back[MAXN];
vector<int> S, P;

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

int kmpSearch(vector<int> S) {
    int res = 0;
    int j = 0;
    for (int i = 0; i < S.size(); i++) {
        while (j >= 0 && S[i] != P[j])
            j = back[j];
        j++;
        if (j == P.size()) {
            res++;
            j = back[j];
        }
    }
    return res;
}

int main() {
    cin >> N >> W;
    for (int i = 0; i < N; i++) {
        cin >> bear[i];
    }
    for (int i = 0; i < W; i++) {
        cin >> elephant[i];
    }
    if (W == 1) {
        cout << N;
        return 0;
    }
    if (N == 1) {
        cout << 0;
        return 0;
    }
    for (int i = 1; i < N; i++) {
        S.push_back(bear[i] - bear[i - 1]);
    }
    for (int i = 1; i < W; i++) {
        P.push_back(elephant[i] - elephant[i - 1]);
    }
    kmpPreprocess();
    cout << kmpSearch(S) << endl;
}