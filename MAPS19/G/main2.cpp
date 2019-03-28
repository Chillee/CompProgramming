#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <stack>
#include <deque>
#include <string.h>
#include <sstream>
#include <bitset>
#include <math.h>
#include <assert.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
template <class T>
using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
template <class T>
using ordered_multiset =
    __gnu_pbds::tree<T, __gnu_pbds::null_type, less_equal<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

#define PI atan2(0, -1)
#define epsilon 1e-9
#define INF 5000000000000000000
#define MOD 1000000007

#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

int N, M, idx = 0, numGood = 0, st, numSeen = 0, inDeg[10010], outDeg[10010];
unordered_map<string, int> animalNum;
vector<int> adjacency[10010];
bool visited[10010];

void bfs(int curr) {
    visited[curr] = true;
    numSeen++;
    for (int nexty : adjacency[curr])
        if (!visited[nexty])
            bfs(nexty);
}

int main() {
    // freopen("feed.in", "r", stdin); freopen("feed.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(10);
    cin >> N >> M;
    for (int aaa = 0; aaa < N; aaa++) {
        string s;
        int nexts;
        cin >> s >> nexts;
        if (animalNum.find(s) == animalNum.end())
            animalNum[s] = idx++;
        bool good = true;
        for (int i = 0; i < nexts; i++) {
            string cc;
            cin >> cc;
            if (animalNum.find(cc) == animalNum.end())
                animalNum[cc] = idx++;
            int a = animalNum[s], b = animalNum[cc];
            cout << a << ' ' << b << endl;
            if (a == b)
                continue;
            adjacency[a].pb(b);
            adjacency[b].pb(a);
            outDeg[a]++;
            inDeg[b]++;
            good = false;
            st = animalNum[s];
        }
        if (good)
            numGood++;
    }
    assert(idx == N);
    if (numGood == N) {
        cout << "FALSE ALARM\n";
        return 0;
    } else {
        bfs(st);
        cout << numSeen << ' ' << numGood << endl;
        if (numSeen != N - numGood) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
        int neg = 0, pos = 0;
        for (int i = 0; i < N; i++) {
            if (inDeg[i] + 1 == outDeg[i])
                neg++;
            else if (inDeg[i] == outDeg[i] + 1)
                pos++;
            else if (inDeg[i] != outDeg[i]) {
                cout << "IMPOSSIBLE\n";
                return 0;
            }
        }
        if (neg == pos && neg < 2)
            cout << "POSSIBLE\n";
        else
            cout << "IMPOSSIBLE\n";
    }
    return 0;
}

/******************************
Kateba ii dake no hanashi darou
Success is only a victory away
- No Game No Life Opening
******************************/