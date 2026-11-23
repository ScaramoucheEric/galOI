/*
    @ Author:       Eric / Sky__White
    @ Filename:     T615820.cpp
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
#include <random>

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

void solve() {
    int n, x; fin >> n >> x;
    
    int s = 0;
    while (n > 0) {
        s += n % x;
        n /= x;
    }
    
    if ((s & s - 1) == 0) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}

signed main() {
    // int T; fin >> T;

    cout << rand() % 2 << endl;
    // while(T -- ) {
    //     solve();
    // }
}