#include <bits/stdc++.h>

// #define endl '\n';
using namespace std;

int T, N;
char x[150];
signed main() {
    // ios::sync_with_stdio(0);
    // cin.tie(0);
    scanf("%d\n", &T);
    for (int t1 = 0; t1 < T; t1++) {
        cin >> N;
        scanf("%d\n", &N);
        for (int t2 = 0; t2 < N; t2++) {
            map<string, string> info;
            for (int j = 0; j < 10; j++) {
                fgets(x, 150, stdin);
                if (j == 0 || j == 9)
                    continue;
                string t(x);
                string key;
                string value;
                int foundKey = -1;
                for (int k = 0; k < t.size(); k++) {
                    // cout << k << ' ' << t[k] << endl;
                    if (t[k] == '=' && foundKey == -1) {
                        key = t.substr(0, k);
                    } else if (t[k] == '{') {
                        foundKey = k + 1;
                    } else if (t[k] == '}') {
                        // cout << "found: " << foundKey << endl;
                        value = t.substr(foundKey, k - foundKey);
                    }
                }
                // cout << key << ' ' << value << endl;
                // cout << j << ' ' << t << endl;
                info[key] = value;
            }
            assert(info.size() == 8);
            string res;
            int last = 0;
            for (int i = 0; i < info["author"].size(); i++) {
                if (info["author"][i] == ' ') {
                    res.append(info["author"].substr(last, 2));
                    res.append(". ");
                    last = i + 1;
                } else if (info["author"][i] == ',' || i == info["author"].size() - 1) {
                    res.append(info["author"].substr(last, 1));
                    if (i != info["author"].size() - 1) {
                        res.append(", ");
                    }
                    i++;
                    last = i + 1;
                }
            }
            res.append(". ");
            res.append(info["title"] + ". ");
            res.append(info["journal"] + ". ");
            res.append(info["year"] + ";");
            res.append(info["volume"] + "(");
            res.append(info["number"] + "):");
            res.append(info["pages"] + ".");
            cout << res << endl;
        }
    }
}