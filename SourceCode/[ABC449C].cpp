/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC449C].cpp
    @ Time:         03/14/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <cstdio>
#include <unordered_map>

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
    int n, l, r; fin >> n >> l >> r;

    string str; cin >> str; str = ' ' + str;

    vector<unordered_map<char, int> > st(n + 1);
    for (int i = 1; i <= n; i ++ )
        st[i][str[i]] ++ ;
    
    for (int i = 1; i <= n; i ++ )
        for (int j = 0; j < 26; j ++ )
            st[i][j + 'a'] += st[i - 1][j + 'a'];
    
    int cnt = 0;
    for (int i = 1; i + l - 1 <= n; i ++ ) {
        cnt += st[min(i + r, n)][str[i]] - st[i + l - 1][str[i]];
        // cout << st[min(i + r, n)][str[i]] << " " << st[i + l - 1][str[i]] << " " << cnt << endl;
    }

    cout << cnt << endl;
}