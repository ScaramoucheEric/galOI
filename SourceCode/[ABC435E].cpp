/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC435E].cpp
    @ Time:         12/06/2025
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <iostream>
#include <set>
#include <algorithm>
#include <cstring>

using namespace std;

#define int long long

signed main() {
    int n, q;
    cin >> n >> q;

    set<pair<int, int> > w;
    w.insert({1, n});

    int wcnt = n;

    for (int i = 0; i < q; i++) {
        int L, R;
        cin >> L >> R;

        auto it = w.lower_bound({L, 0});
        if (it != w.begin()) {
            auto pit = prev(it);
            if (pit->first <= L && pit->second >= L) {
                it = pit;
            }
        }

        while (it != w.end() && it->first <= R) {
            int l = it->first;
            int r = it->second;

            it = w.erase(it);
            wcnt -= (r - l + 1);

            if (l < L) {
                w.insert({l, L - 1});
                wcnt += (L - l);
            }
            if (r > R) {
                w.insert({R + 1, r});
                wcnt += (r - R);
            }
        }

        cout << wcnt << '\n';
    }

    return 0;
}