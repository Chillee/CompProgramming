#include <bits/stdc++.h>

using namespace std;

set<string> gems;
int N;
int main() {
    cin >> N;
    gems.insert("purple");
    gems.insert("green");
    gems.insert("blue");
    gems.insert("orange");
    gems.insert("red");
    gems.insert("yellow");
    for (int i = 0; i < N; i++) {
        string t;
        cin >> t;
        gems.erase(t);
    }
    cout << gems.size() << endl;
    for (auto i : gems) {
        if (i == "purple") {
            cout << "Power" << endl;
        } else if (i == "green") {
            cout << "Time" << endl;
        } else if (i == "blue") {
            cout << "Space" << endl;
        } else if (i == "orange") {
            cout << "Soul" << endl;
        } else if (i == "red") {
            cout << "Reality" << endl;
        } else if (i == "yellow") {
            cout << "Mind" << endl;
        }
    }
}