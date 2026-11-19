/*
    @ Author:       Eric / Sky__White
    @ Filename:     T664073.cpp
    @ Date:         05/04/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <functional>
#include <cstdio>
#include <queue>

namespace std {
    class Read {
        public:
        template<typename T>
        inline Read operator >> (T & x) {
            T sum = 0, opt = 1;
            char ch = getchar();
            while(!isdigit(ch)) opt = (ch == '-') ? -1 : 1, ch = getchar();
            while( isdigit(ch)) sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
            x = sum * opt; return *this;
        }
    };
}
#define int long long
#define all(a) a.begin(), a.end()

using namespace std; Read fin;

signed main() {
    int n, t; fin >> n >> t;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        fin >> a[i];
    }

    int ans = 0;
    for (int i = 0; i < n - 1; ++i) {
        int start = max(a[i], a[i+1]);
        if (start < t) {
            ans += (t - start);
        }
    }

    cout << ans << "\n";
    return 0;
}