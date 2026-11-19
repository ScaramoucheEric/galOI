/*
    @ Author:       Eric / Sky__White
    @ Filename:     P3435.cpp
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

    vector<int> ne(m + 1);

    for (int i = 2, j = 0; i <= m; i ++ ) {
        while(j and p[i] != p[j + 1]) j = ne[j];
        if (p[i] == p[j + 1]) j ++ ;
        ne[i] = j;
    }

    vector<int> fail(m + 1, -1);

    function<int(int)> dfs = [&](int x) -> int {
        if (fail[x] != -1) return fail[x];
        if (ne[x] == 0) return fail[x] = x;
        return fail[x] = dfs(ne[x]);
    };

    // for (int i = 1; i <= m; i ++ )
    //     cout << i << " ";
    // cout << endl;
    // for (int i = 1; i <= m; i ++ )
    //     cout << ne[i] << " ";
    // cout << endl;
    // for (int i = 1; i <= m; i ++ ) {
    //     cout << dfs(i) << " ";
    // }
    // cout << endl;
    // for (int i = 1; i <= m; i ++ )
    //     cout << p[i] << " ";
    // cout << endl;
    // for (int i = 1; i <= m; i ++ ) {
    //     cout << i - dfs(i) << " ";
    // }
    // cout << endl;

    int sum = 0;
    for (int i = 1; i <= m; i ++ )
        sum += i - dfs(i);
    
    cout << sum << endl;
    
    // for (int i = 1, j = 0; i <= n; i ++ ) {
    //     while(j and s[i] != p[j + 1]) j = ne[j];
    //     if (s[i] == p[j + 1]) j ++ ;
    //     if (j == m) {
    //         cout << i - m << " ";
    //         j = ne[j];
    //     }
    // }
}