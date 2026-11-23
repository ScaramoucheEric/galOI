/*
    @ Author:       Eric / Sky__White
    @ Filename:     T663578.cpp
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
    int n, m, d; fin >> n >> m >> d;

    int res = 0;

    if (m / (d + 1) < n) return 0 & puts("-1");
    else {
        m -= n * (d + 1);
        while(m -- and n -- ) {
            res ++ ;
        }
        m ++ ;
        if (m) {
            // cout << m << endl;
            res += m / (d + 1);
        }

        cout << res << endl;
    }

    return 0;
}