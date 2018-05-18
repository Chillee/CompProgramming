#include <bits/stdc++.h>

using namespace std;

string P;
int T;
int D;

int main() {
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin >> D >> P;
        int numChanges = 0;
        while (true) {
            int dmg = 0;
            int pwr = 1;
            for (int i = 0; i < P.size(); i++) {
                if (P[i] == 'C') {
                    pwr *= 2;
                } else {
                    dmg += pwr;
                }
            }
            if (dmg <= D) {
                break;
            }
            int pos = -1;
            for (int i = P.size() - 1; i > 0; i--) {
                if (P[i] == 'S' && P[i - 1] == 'C') {
                    pos = i;
                }
            }
            if (pos == -1) {
                numChanges = -1;
                break;
            }
            swap(P[pos], P[pos - 1]);
            numChanges++;
        }
        if (numChanges == -1) {
            cout << "Case #" << t + 1 << ": IMPOSSIBLE" << endl;
        } else {

            cout << "Case #" << t + 1 << ": " << numChanges << endl;
        }
    }
}