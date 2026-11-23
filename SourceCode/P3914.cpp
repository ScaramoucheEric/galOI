/*
    @ Author:       Eric / Sky__White
    @ Filename:     P3914.cpp
    @ Time:         12/18/2025
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

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
    int n, m; fin >> n >> m;

    vector<vector<int> > k(n + 1);

    for (int i = 1; i <= n; i ++ ) {
        int x; fin >> x; k[i].push_back(x);

        for (int j = 1; j <= k[i][0]; j ++ )
            fin >> x, k[i].push_back(x);
    }

    
}