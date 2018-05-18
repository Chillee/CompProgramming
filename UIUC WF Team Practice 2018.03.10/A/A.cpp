#include <bits/stdc++.h>

using namespace std;

int main() {
    while (true) {
        int t;
        cin>> t;
        if (t==0) {
            break;
        }
        vector<int> possibles{1, 64, 729, 4096, 15625, 46656, 117649, 262144, 531441, 1000000, 1771561, 2985984, 4826809, 7529536, 11390625, 16777216, 24137569, 34012224, 47045881, 64000000, 85766121};
        bool f = false;
        for (auto i: possibles) {
            if (t==i) {
                cout<<"Special"<<endl;
                f = true;
                break;
            }
        }
        if (!f) {
            cout<<"Ordinary"<<endl;
        }
    }
}