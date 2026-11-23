/*
    @ Author:       Eric / Sky__White
    @ Filename:     [AcWing1072].cpp
    @ Time:         11/28/2025
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
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

using PII = pair<int,int> ;

signed main() {
    int n; fin >> n;
    vector<vector<PII> > G(n + 1);

    for (int i = 1; i < n; i ++ ) {
        int a, b, c; fin >> a >> b >> c;
        G[a].push_back({b, c});
        G[b].push_back({a, c});
    }

    vector<int> dp[2];

    dp[1].resize(n + 1), dp[0] = dp[1];

    int res = 0;

    function<void(int, int)> dfs = [&](int u, int fa) {
        // cout << u << ":" << endl;
        // for (int i = 1; i <= n; i ++ ) {
        //     for (int j = 0; j <= 1; j ++ )
        //         cout << dp[j][i] << " ";
        //     cout << endl;
        // }
        // cout << endl;
        for (auto [v, w] : G[u]) {
            if (v == fa) continue;
            dfs(v, u);
            if (dp[0][v] + w > dp[0][u]) {
                dp[1][u] = dp[0][u];
                dp[0][u] = w + dp[0][v];
            } else dp[1][u] = max(dp[1][u], dp[0][v] + w);
        }
        res = max(res, dp[1][u] + dp[0][u]);

        // for (int i = 1; i <= n; i ++ ) {
        //     for (int j = 0; j <= 1; j ++ )
        //         cout << dp[j][i] << " ";
        //     cout << endl;
        // }
        // cout << endl << endl;
    };

    dfs(1, 1);

    cout << res << endl;

    // for (int i = 1; i <= n; i ++ ) {
    //     for (int j = 0; j <= 1; j ++ )
    //         cout << dp[j][i] << " ";
    //     cout << endl;
    // }
    // cout << endl;

    return 0;
}