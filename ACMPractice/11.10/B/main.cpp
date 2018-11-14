#include <bits/stdc++.h>
using namespace std;

set<int> t1 = {0, 2, 4, 6, 7, 9, 11};
set<int> t2 = {0, 2, 4, 5, 7, 9, 11};
set<int> t3 = {0, 2, 3, 5, 7, 8, 10};
set<int> t4 = {1, 2, 4, 6, 8, 9, 11};
set<int> t5 = {0, 2, 3, 5, 7, 9, 10};

set<int> table[] = {t1, t2, t3, t4, t5};

vector<int> freqs;
set<int> freqs_set;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        double F;
        cin >> F;
        int x = ((int)round(12. * log2(F) - 12. * log2(13.5) + 0.0000001) + 9) % 12;
        freqs.push_back(x);
        freqs_set.insert(x);
    }
    int cnt = 5, passed = -1;
    for (int i = 0; i < 5; i++) {
        bool success = true;
        for (int j : freqs_set) {
            if (table[i].find(j) == table[i].end()) {
                cnt--;
                success = false;
                break;
            }
        }
        if (success) {
            passed = i;
        }
    }
    if (cnt != 1) {
        cout << "cannot determine key" << endl;
        return 0;
    }
    switch (passed) {
    case 0:
        cout << "G major" << endl;
        break;
    case 1:
        cout << "C major" << endl;
        break;
    case 2:
        cout << "Eb major" << endl;
        break;
    case 3:
        cout << "F# minor" << endl;
        break;
    case 4:
        cout << "G minor" << endl;
        break;
    }

    for (int i : freqs) {
        switch (i) {
        case 0:
            cout << "C"
                 << "\n";
            break;
        case 1:
            cout << "C#"
                 << "\n";
            break;
        case 2:
            cout << "D"
                 << "\n";
            break;
        case 3:
            cout << "Eb"
                 << "\n";
            break;
        case 4:
            cout << "E"
                 << "\n";
            break;
        case 5:
            cout << "F"
                 << "\n";
            break;
        case 6:
            cout << "F#"
                 << "\n";
            break;
        case 7:
            cout << "G"
                 << "\n";
            break;
        case 8:
            cout << (passed == 3 ? "G#" : "Ab") << "\n";
            break;
        case 9:
            cout << "A"
                 << "\n";
            break;
        case 10:
            cout << "Bb"
                 << "\n";
            break;
        case 11:
            cout << "B"
                 << "\n";
            break;
        }
    }

    return 0;
}