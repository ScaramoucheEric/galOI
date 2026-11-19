/*
    @ Author:       Eric / Sky__White
    @ Filename:     P17835.cpp
    @ Date:         07/11/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <functional>

namespace std {
    class Read {
        public:
        template<typename T>
        inline Read operator >>(T & x) {
            T sum = 0; short opt = 1;
            char ch = getchar();
            while(!isdigit(ch)) opt = (ch == '-') ? -1 : 1, ch = getchar();
            while( isdigit(ch)) sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
            x = sum * opt; return *this;
        }
    };
}
#define int long long
#define all(a) a.begin(), a.end()
#define IO(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout);
#define endl "\n"

using namespace std; Read fin;

signed main() {
    string str; int n; fin >> n; cin >> str; str = " " + str;

    unordered_map<string, int> cnt;

    for (int i = 1; i <= n - 2; i ++ ) {
        string a, b, c; a.push_back(str[i]), b.push_back(str[i + 1]), c.push_back(str[i + 2]);
        if (a == b or b == c or c == a) ; else
            cnt[a + b + c] ++ ;
    }

    int res = 0;

    for (auto i : cnt) {
        // cout << i.first << " " << i.second << endl;
        res = max(res, i.second);
    }

    cout << res << endl;
}