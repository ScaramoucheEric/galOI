/*
    @ Author:       Eric / Sky__White
    @ Filename:     P8386.cpp
    @ Date:         25/07/2026
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
        inline Read operator >> (T & x) {
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

using namespace std; Read fin;

const int Mod = 1e9 + 7;

signed main() {
    int n, m; fin >> n >> m;
    vector<vector<int> > f(n + 1, vector<int>(n + 1)), g(n + 1, vector<int>(n + 1));
    g[0][0] = 1;

    for (int i = 1; i <= n; i ++ ) {
        for (int j = 1; j <= min(i, m); j ++ ) {
            g[i][j] = f[i - 1][j] * j;
            f[i][j] = f[i - 1][j] * (m - j);
            g[i][j] += g[i - 1][j] * j;
            f[i][j] += g[i - 1][j - 1] * (m - j + 1);
            f[i][j] %= Mod;
            g[i][j] %= Mod;
        }
    }

    int res = 0;
    for (int i = 0; i <= n; i ++ )
        (res += g[n][i]) %= Mod;

    cout << res << endl;
}