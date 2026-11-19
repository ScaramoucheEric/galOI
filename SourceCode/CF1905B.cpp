/*
    @ Author:       Eric / Sky__White
    @ Filename:     CF1905B.cpp
    @ Date:         03/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <cstdio>

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
    } fin;
}

#define int long long
#define all(a) a.begin(), a.end()

using namespace std;

signed main() {
    int T; fin >> T;

    while(T -- ) {
        int n; fin >> n;

        vector<int> d(n + 1, 0);
        for (int i = 1, a, b; i < n; i ++ )
            fin >> a >> b, d[a] ++ , d[b] ++ ;
        
        int cnt = 0;
        for (int i = 1; i <= n; i ++ )
            if (d[i] == 1) cnt ++ ;

        cout << (cnt + 1 >> 1) << endl;
    }

    return 0;
}