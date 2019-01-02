#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

using namespace __gnu_pbds;
typedef pair<int, int> pii;
// typedef pair<int, int> key;
// typedef gp_hash_table<
//     int, int, hash<int>, equal_to<int>, direct_mask_range_hashing<int>, linear_probe_fn<>,
//     hash_standard_resize_policy<hash_exponential_size_policy<>, hash_load_check_resize_trigger<true>, true>>
//     ht;

typedef int key;
typedef pair<key, int> vec_t;

const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
    int operator()(int x) const {
        return x;
        x = ((x >> 16) ^ x) * 0x119de1f3;
        x = ((x >> 16) ^ x) * 0x119de1f3;
        x = (x >> 16) ^ x;
        return x;
    }
};
int block;

void benchmarkgp(string msg, vector<vec_t> &vals, int NUM_ITERS) {
    clock_t begin = clock();
    gp_hash_table<int, int, chash> test;

    for (int t = 0; t < NUM_ITERS; t++) {
        for (auto i : vals) {
            test[i.first] = test[i.first] + i.second * t;
        }
    }
    block += test[0];
    cout << msg << ": " << string(60 - msg.size(), ' ') << "\t" << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;
}

void benchmarkcc(string msg, vector<vec_t> &vals, int NUM_ITERS) {
    clock_t begin = clock();
    cc_hash_table<key, int, chash> test;
    for (int t = 0; t < NUM_ITERS; t++) {
        for (auto i : vals) {
            test[i.first] = test[i.first] + i.second * t;
        }
    }
    block += test[0];
    cout << msg << ": " << string(60 - msg.size(), ' ') << "\t" << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;
}

void benchmarkStl(string msg, vector<vec_t> &vals, int NUM_ITERS) {
    clock_t begin = clock();
    unordered_map<key, int, chash> test;
    for (int t = 0; t < NUM_ITERS; t++) {
        for (auto i : vals) {
            test[i.first] = test[i.first] + i.second * t;
        }
    }
    block += test[0];
    cout << msg << ": " << string(60 - msg.size(), ' ') << "\t" << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;
}
void benchmarkArray(string msg, vector<vec_t> &vals, int NUM_ITERS) {
    clock_t begin = clock();
    int test[(int)1e6];
    for (int t = 0; t < NUM_ITERS; t++) {
        for (auto i : vals) {
            test[i.first] = test[i.first] + i.second * t;
        }
    }
    block += test[0];
    cout << msg << ": " << string(60 - msg.size(), ' ') << "\t" << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;
}

void benchmark(string msg, vector<vec_t> vals, int NUM_ITERS) {
    benchmarkArray("array " + msg, vals, NUM_ITERS);
    benchmarkgp("gp_hash_table " + msg, vals, NUM_ITERS);
    benchmarkcc("cc_hash_table " + msg, vals, NUM_ITERS);
    benchmarkStl("unordered_map " + msg, vals, NUM_ITERS);
    // becnh
    cout << endl;
}

vector<vec_t> generateVec(int max_val, bool shuffled) {
    vector<int> k(max_val), v(max_val);
    vector<vec_t> vals;
    iota(k.begin(), k.end(), 0);
    iota(v.begin(), v.end(), 0);
    if (shuffled) {
        random_shuffle(k.begin(), k.end());
        random_shuffle(v.begin(), v.end());
    }
    for (int i = 0; i < max_val; i++) {
        vals.push_back({k[i], v[i]});
    }
    return vals;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    // benchmark("linear insertion", generateVec(1e7, false), 1);
    // benchmark("linear read/write", generateVec(1e5, false), 1000);
    benchmark("random insertion", generateVec(1e5, true), 10000);
    // benchmark("random read/write", generateVec(1e5, true), 1000);
}