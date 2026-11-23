/*
    @ Author:       Eric / Sky__White
    @ Filename:     外卖之王.cpp
    @ Date:         11/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
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

const int Mod = 1e9 + 7;

signed main() {
    freopen("takeout.in", "r", stdin);
    freopen("takeout.out", "w", stdout);
    int n, L; fin >> n >> L;

    vector<int> a(n + 1), b(n + 1);
    a[0] = L, b[0] = 0;

    int res = 0;

    for (int i = 1; i <= n; i ++ )
        fin >> a[i] >> b[i], res += abs(a[i] - b[i]);

    sort(all(a)); sort(all(b));

    for (int i = 0; i <= n; i ++ )
        res += abs(a[i] - b[i]);

    cout << res << endl;
}