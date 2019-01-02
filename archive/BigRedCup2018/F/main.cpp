#include <bits/stdc++.h>

using namespace std;

int main() {
    for (int i = 0; i < 9; i++) {
        cout << i << endl;
        cout << flush;
        string t;
        getline(cin, t);
        if (t == "great!" || t == "don't think so" || t == "don't touch me!" || t == "not bad" || t == "cool") {
            cout << "normal" << endl;
            break;
        } else if (t == "don't even" || t == "are you serious?" || t == "go die in a hole" || t == "worse" ||
                   t == "terrible" || t == "no way") {
            cout << "grumpy" << endl;
            break;
        }
    }
}