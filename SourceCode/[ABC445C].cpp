/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC445C].cpp
    @ Time:         02/14/2026
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

signed main() {
    int n; fin >> n;
    vector<int> arr(n + 1);
    vector<int> dp(n + 1, -1);

    for (int i = 1; i <= n; i ++ ) {
        fin >> arr[i];
    }

    function<int(int)> dfs = [&](int id) {
        if (dp[id] != -1) return dp[id];
        if (arr[id] == id) return dp[id] = id;
        return dp[id] = dfs(arr[id]);
    };

    for (int i = 1; i <= n; i ++ )
        cout << dfs(i) << " ";
}