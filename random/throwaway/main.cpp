#include <bits/stdc++.h>
using namespace std;
// https://codeforces.com/blog/entry/50770

#define scanfd1(x) scanf("%d", &x)
#define scanfd2(x, y) scanf("%d %d", &x, &y)
#define scanfd3(x, y, z) scanf("%d %d %d", &x, &y, &z)
#define scanfd4(x, y, z, w) scanf("%d %d %d %d", &x, &y, &z, &w)

#define scanfll1(x) scanf("%lld", &x)
#define scanfll2(x, y) scanf("%lld %lld", &x, &y)
#define scanfll3(x, y, z) scanf("%lld %lld %lld", &x, &y, &z)
#define scanfll4(x, y, z, w) scanf("%lld %lld %lld %lld", &x, &y, &z, &w)

#define fi(n) for (int i = 0; i < (n); ++i)
#define fj(n) for (int j = 0; j < (n); ++j)
#define fk(n) for (int k = 0; k < (n); ++k)

#define ll long long int

#define pb push_back

#define all(a) a.begin(), a.end()

#define fir first
#define sec second
typedef pair<int, int> pii;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

#define map gp_hash_table
int hash_f(int x) { return (x >> 16) ^ x; }
int hash_combine(int a, int b) { return a * 31 + b; }
struct chash {
    int operator()(int x) const { return hash_f(x); }
};
#define PI 3.1415926535897932384626

map<int, bool> mp; // map

struct vals {
    bool vd;                 // true if variable is defined by only one fixed number (not operations)
    char val[1010];          // the string that represents the fixed number if exists
    string nome, v1, v2, op; // v1 and v2 are the operands if !vd
} s[5020];

bool valdef(string var, bool k) {
    if (var == "?")
        return k;
    return mp[hash<string>{}(var)];
}

bool value(string v1, string v2, string op, bool k) {
    if (op == "XOR") {
        return valdef(v1, k) ^ valdef(v2, k);
    } else if (op == "OR") {
        return valdef(v1, k) | valdef(v2, k);
    } else if (op == "AND") {
        return valdef(v1, k) & valdef(v2, k);
    }
    return true;
}

int main() {
    int n, m;
    char c;
    char aux1[12], aux2[1010], aux3[5], aux4[12];
    string sauxmax, sauxmin;
    cin >> n >> m;

    fi(n) {
        scanf("%s := %s%c", aux1, aux2, &c);
        s[i].nome = string(aux1);

        if (c == ' ') {
            scanf("%s %s", aux3, aux4);
            s[i].v1 = string(aux2);
            s[i].op = string(aux3);
            s[i].v2 = string(aux4);
            s[i].vd = false;
        } else if (c == '\n' or c == '\r') {
            strcpy(s[i].val, aux2);
            s[i].vd = true;
        } else
            cout << "erro" << endl;
    }

    sauxmax = "";
    sauxmin = "";

    fi(m) {                      // for each i digit in the m-bit value
        vector<int> vsoma(2, 0); // sum of the n ith digits considering if ith-digit of ? is 0 or 1

        fk(2) { // simulating if the ith digit of "?" is 0 then 1

            mp.clear();
            // simulation is 0 or 1
            fj(n) { // for each variable

                bool baux;
                if (s[j].vd)
                    baux = mp[hash<string>{}(s[j].nome)] = s[j].val[i] - '0';
                else {
                    baux = mp[hash<string>{}(s[j].nome)] = value(s[j].v1, s[j].v2, s[j].op, k);
                }
                vsoma[k] += baux;
            }
        }

        if (vsoma[1] > vsoma[0])
            sauxmax += '1', sauxmin += '0';
        else if (vsoma[1] == vsoma[0])
            sauxmax += '0', sauxmin += '0';
        else if (vsoma[1] < vsoma[0])
            sauxmax += '0', sauxmin += '1';
    }

    cout << sauxmin << endl << sauxmax << endl;
}