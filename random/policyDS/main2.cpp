
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

typedef gp_hash_table<
    int, null_type, hash<int>, equal_to<int>, direct_mask_range_hashing<int>, linear_probe_fn<>,
    hash_standard_resize_policy<hash_exponential_size_policy<>, hash_load_check_resize_trigger<true>, true>>
    gp;

typedef gp_hash_table<
    int, null_type, hash<int>, equal_to<int>, direct_mask_range_hashing<int>, linear_probe_fn<>,
    hash_standard_resize_policy<hash_exponential_size_policy<>, hash_load_check_resize_trigger<true>, true>>
    gp2;

const int n = 1e7;
int getticks() {
    static auto starttime = std::chrono::high_resolution_clock::now();
    auto t = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(t - starttime).count();
}
int main() {
    gp table;
    int s = getticks();
    for (int i = 0; i < n; i++)
        table.insert(i);
    for (int i = 0; i < n; i++)
        table.erase(i);

    cout << getticks() - s << endl;
    s = getticks();
    gp2 table2;
    // table.resize(n);
    table.set_loads({.125, 1});

    for (int i = 0; i < n; i++)
        table2.insert(i);
    for (int i = 0; i < n; i++)
        table2.erase(i);
    cout << getticks() - s << endl;
    return 0;
}
