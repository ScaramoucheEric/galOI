/*
    @ Author:       Eric / Sky__White
    @ Filename:     CF11D.cpp
    @ Date:         20/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <functional>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
#include <queue>
#include <ctime>

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
    // freopen("circle.in", "r", stdin);
    // freopen("circle.out", "w", stdout);

    int n, m; fin >> n >> m;

    vector<vector<int> > G(n + 1);
    vector<vector<int> > cnt(n + 1, vector<int>(n + 1));

    for (int i = 1; i <= m; i ++ ) {
        int u, v; fin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
        cnt[u][v] ++ , cnt[v][u] ++ ;
    }

    vector<vector<int> > dp(1 << n, vector<int>(n + 1));
    
    for (int i = 1; i <= n; i ++ )
        dp[1 << i - 1][i] = 1;

    for (int S = 1; S < 1 << n; S ++ ) {
        int rt = log2(S) + 1.000000003;

        for (int u = 1; u <= rt; u ++ ) {
            if (S & (1 << u - 1)) for (int v = 1; v <= rt; v ++ )
                if (~S & (1 << v - 1)) {
                    (dp[S | (1 << v - 1)][v] += dp[S][u] * cnt[u][v]);
                }
        }
    }

    int ans = 0;

    function<int(int)> lowbit = [&](int x) -> int {
        return x & -x;
    };

    for (int S = 1; S < 1 << n; S ++ ) {
        int rt = log2(S) + 1.000000003;
        if (S - lowbit(S) == 0) continue;

        for (int u = 1; u <= rt; u ++ ) {
            int &v = rt;

            if (u == v) continue;
            if (~S & (1 << u - 1)) continue;
            (ans += dp[S][u] * cnt[u][v]);
        }
    }

    ans = ans - m; ans /= 2;

    cout << ans << endl;
}