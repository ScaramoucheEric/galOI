/*
    @ Author:       Eric / Sky__White
    @ Filename:     P1131.cpp
    @ Time:         11/20/2025
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
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

using namespace std;

#define int long long
#define all(a) a.begin(), a.end()

using PII = pair<int,int> ;

signed main() {
    int n, s; fin >> n >> s;

    vector<vector<PII> > G(n + 1);

    for (int i = 1; i < n; i ++ ) {
        int a, b, c; fin >> a >> b >> c;
        G[a].push_back({b, c});
        G[b].push_back({a, c});
    }

    vector<int> dp(n + 1);

    function<void(int, int)> dfs = [&](int u, int fa) {
        for (auto [v, w] : G[u]) {
            if (v == fa) continue;
            dfs(v, u);
            dp[u] = max(dp[u], dp[v] + w);
        }
    };

    dfs(s, s);

    // for (int i = 1; i <= n; i ++ )
    //     cout << i << " " << dp[i] << endl;

    int res = 0;

    dfs = [&](int u, int fa) {
        for (auto [v, w] : G[u]) {
            if (v == fa) continue;
            dfs(v, u);
            res += dp[u] - dp[v] - w;
        }
    };

    dfs(s, s);

    cout << res << endl;

    return 0;
}
