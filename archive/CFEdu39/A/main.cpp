#include <bits/stdc++.h>

using namespace std;

int main() {
    int N;
    cin>>N;
    int possum = 0;
    int negsum = 0;
    for (int i=0; i<N; i++) {
        int t;
        cin>>t;
        possum = max(possum, possum + t);
        negsum = min(negsum, negsum + t);
    }
    cout<< possum - negsum<<endl;
}

