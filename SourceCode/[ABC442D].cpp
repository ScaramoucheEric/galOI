/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC442D].cpp
    @ Time:         01/24/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <functional>

using namespace std;

#define int long long
#define all(a) a.begin(), a.end()

class BIT {
    public:
        vector<int> bit;
        int n;
        BIT(int n) : n(n), bit(n + 2, 0) {}
        
        void update(int idx, int delta) {
            for (; idx <= n; idx += idx & -idx)
                bit[idx] += delta;
        }
        
        int query(int idx) {
            int sum = 0;
            for (; idx > 0; idx -= idx & -idx)
                sum += bit[idx];
            return sum;
        }
        
        int sum(int l, int r) {
            return query(r) - query(l - 1);
        }
};

signed main() {
    int n, q; cin >> n >> q;
    
    vector<int> arr(n + 1);
    BIT bit(n);
    
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
        bit.update(i, arr[i]);
    }
    
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int x;
            cin >> x;

            bit.update(x, arr[x + 1] - arr[x]);
            bit.update(x + 1, arr[x] - arr[x + 1]);

            swap(arr[x], arr[x + 1]);
        } else {
            int l, r;
            cin >> l >> r;
            cout << bit.sum(l, r) << '\n';
        }
    }
    
    return 0;
}