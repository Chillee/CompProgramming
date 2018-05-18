#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll a;
ll b;
void rec() {
    if (a == 0 || b== 0) {return;}
    if (a >= 2*b) {
        a = a%(2*b);
        rec();
    } else if (b >= 2*a) {
        b = b%(2*a);
        rec();
    } else {
        return;
    }
}
int main() {
    cin >> a>> b;
    rec();
    cout<<a<<' '<<b<<endl;
}