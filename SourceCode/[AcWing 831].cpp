/*
    @ Author:       Eric / Sky__White
    @ Filename:     [AcWing831].cpp
    @ Time:         11/25/2025
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
    } fin;
}
#define int long long
#define all(a) a.begin(), a.end()

using namespace std;

const int INF = 0x3f3f3f3f3f3f3f3f;

signed main() {
    int m; fin >> m;
    char p[m + 2]; scanf("%s", p + 1);
    int n; fin >> n;
    char s[n + 2]; scanf("%s", s + 1);

    vector<int> ne(m + 1);

    for (int i = 2, j = 0; i <= m; i ++ ) {
        while(j and p[i] != p[j + 1]) j = ne[j];
        if (p[i] == p[j + 1]) j ++ ;
        ne[i] = j;
    }

    // for (int i = 1; i <= m; i ++ )
    //     cout << ne[i] << " ";
    // cout << endl;
    
    for (int i = 1, j = 0; i <= n; i ++ ) {
        while(j and s[i] != p[j + 1]) j = ne[j];
        if (s[i] == p[j + 1]) j ++ ;
        if (j == m) {
            cout << i - m << " ";
            j = ne[j];
        }
    }
}