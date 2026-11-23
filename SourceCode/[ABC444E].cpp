/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC444E].cpp
    @ Time:         02/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <functional>
#include <set>
#include <map>

using namespace std;
#define int long long

signed main() {
    int n, d; cin >> n >> d;
    
    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    multiset<int> val;
    multiset<int> diffs; 

    auto add_diff = [&](int diff) {
        if (diff != LLONG_MAX) {
            diffs.insert(diff);
        }
    };

    auto remove_diff = [&](int diff) {
        if (diff != LLONG_MAX) {
            diffs.erase(diffs.find(diff));
        }
    };

    int ans = 0;
    int r = 0;

    for (int L = 0; L < n; L++) {
        while (r < n) {
            if (val.empty()) {
                val.insert(arr[r]);
                r++;
                continue;
            }
            
            auto it = val.lower_bound(arr[r]);
            int l_d = LLONG_MAX;
            int r_d = LLONG_MAX;
            
            if (it != val.begin()) {
                auto prev_it = prev(it);
                l_d = arr[r] - *prev_it;
            }
            
            if (it != val.end()) {
                r_d = *it - arr[r];
            }
            
            if (l_d < d or r_d < d) {
                break;
            }
            
            if (it != val.end() and it != val.begin()) {
                auto prev_it = prev(it);
                int old_diff = *it - *prev_it;
                remove_diff(old_diff);
            }
            
            if (it != val.begin()) {
                auto prev_it = prev(it);
                add_diff(arr[r] - *prev_it);
            }
            if (it != val.end()) {
                add_diff(*it - arr[r]);
            }
            val.insert(arr[r]);
            r++;
        }
        
        ans += (r - L);
        
        if (L < r) {
            auto it = val.find(arr[L]);
            
            auto prev_it = (it != val.begin()) ? prev(it) : val.end();
            auto next_it = next(it);
            
            if (prev_it != val.end() and next_it != val.end()) {
                
                int old_diff = *next_it - *prev_it;
                add_diff(old_diff);
            }
            if (prev_it != val.end()) {
                remove_diff(arr[L] - *prev_it);
            }
            if (next_it != val.end()) {
                remove_diff(*next_it - arr[L]);
            }
            val.erase(it);
        }
    }

    cout << ans << "\n";

    return 0;
}