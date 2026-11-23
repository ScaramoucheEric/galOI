/*
    @ Author:       Eric / Sky__White
    @ Filename:     P17831.cpp
    @ Date:         07/11/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <functional>

namespace std {
    class Read {
        public:
        template<typename T>
        inline Read operator >>(T & x) {
            T sum = 0; short opt = 1;
            char ch = getchar();
            while(!isdigit(ch)) opt = (ch == '-') ? -1 : 1, ch = getchar();
            while( isdigit(ch)) sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
            x = sum * opt; return *this;
        }
    };
}
#define int long long
#define all(a) a.begin(), a.end()
#define IO(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout);
#define endl "\n"

using namespace std; Read fin;

signed main() {
    #ifndef ONLINE_JUDGE
    IO("P17831");
    #endif

    int n, m; fin >> n >> m;

    vector<int> arr(n + 1), pre(n + 1);
    for (int i = 1; i <= n; i ++ ) {
        fin >> arr[i];
    }

    sort(1 + all(arr));

    for (int i = 1; i <= n; i ++ ) {
        pre[i] = pre[i - 1] + arr[i];
    }

    int res = 0;

    for (int i = 1; i <= n; i ++ ) {
        int l = 1, r = i;

        while(l <= r) {
            int mid = l + r >> 1;

            if (mid * arr[i] - (pre[i] - pre[i - mid]) <= m) {
                res = max(res, mid);
                l = mid + 1;
            } else {
                r = mid - 1;
            }

            // cout << l << " " << r << " " << mid << " " << res << endl;
        }
    }

    cout << res << endl;
}