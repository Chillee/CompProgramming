#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

int N;
priority_queue<pii, vector<pii>, greater<pii>> introverts;
priority_queue<pii> extroverts;
int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        int w;
        cin >> w;
        introverts.push(pii(w, i + 1));
    }
    for (int i = 0; i < 2 * N; i++) {
        char curType;
        cin >> curType;
        if (curType == '0') {
            auto t = introverts.top();
            introverts.pop();
            cout << t.second << ' ';
            extroverts.push(t);
        } else {
            auto t = extroverts.top();
            extroverts.pop();
            cout << t.second << ' ';
        }
    }
}