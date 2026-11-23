/*
    @ Author:       Eric / Sky__White
    @ Filename:     P3258.cpp
    @ Date:         06/04/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <vector>

namespace std {
    class Read {
        public:
        template<typename T>
        inline Read operator << (T & x) {
            T sum = 0, opt = 1;
            char ch = getchar();
            while(!isdigit(ch)) opt = (ch == '-') ? -1 : 1, ch = getchar();
            while( isdigit(ch)) sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
            x = sum * opt; return *this;
        }
    };
}
using namespace std; Read fin;

#define int long long
#define all(a) a.begin(), a.end()

signed main() {
    int n; fin >> n;

    vector<int> arr(n + 1);

    for (int i = 1; i <= n; i ++ )
        fin >> arr[i];
    
    vector<int> G(n + 1);

    for (int i = 1; i < n; i ++ ) {
        int a, b; fin >> a >> b;
    
        G[a].push_back(b);
        G[b].push_back(a);
    }
}