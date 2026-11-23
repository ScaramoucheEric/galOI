/*
    @ Author:       Eric / Sky__White
    @ Filename:     P15445.cpp
    @ Date:         10/07/2026
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

void solve() {
    int x, y, z; fin >> x >> y >> z;

    if (x > z) {
        puts("NO");
        return ;
    }

    int a = x, b = 0;

    for (int i = 30; ~i; i -- ) {
        if (abs(a - b) <= y and a + b <= z and a != b) { puts("YES"); return ; }
        if (abs(a - b) > y and x >> i & 1) {
            if (a + b + (1 << i) <= z) b |= (1 << i);
            else a -= (1 << i), b |= (1 << i);
        }
    }

    cout << "NO" << endl;
}

signed main() {
    int T; fin >> T;

    while(T -- ) {
        solve();
    }
}