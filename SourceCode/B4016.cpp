/*
    @ Author:       Eric / Sky__White
    @ Filename:     B4016.cpp
    @ Date:         06/01/2026
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

    vector<vector<int> > G(n + 1);

    int res = 0;

    for (int i = 1; i < n; i ++ ) {
        int u, v; fin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    vector<int> dp(n + 1);

    function<void(int, int)> dfs = [&](int u, int fa) -> void {
        for (auto v : G[u]) {
            if (v == fa) continue;
            dfs(v, u);
            res = max(res, dp[u] + dp[v] + 1);
            dp[u] = max(dp[u], dp[v] + 1);
        }
    };

    dfs(1, 1);

    cout << res << endl;
}