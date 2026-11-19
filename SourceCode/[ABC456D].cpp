/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC456D].cpp
    @ Date:         05/02/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
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

const int Mod = 998244353;

signed main() {
    string str; cin >> str;
    int n = str.size();

    long long dp0 = 0, dp1 = 0, dp2 = 0;
    
    for (char ch : str) {
        if (ch == 'a') {
            dp0 = (dp0 + dp1 + dp2 + 1) % Mod;
        } else if (ch == 'b') {
            dp1 = (dp1 + dp0 + dp2 + 1) % Mod;
        } else { // ch == 'c'
            dp2 = (dp2 + dp0 + dp1 + 1) % Mod;
        }
    }
    
    int ans = (dp0 + dp1 + dp2) % Mod;
    cout << ans << endl;
    
    return 0;
}