#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <cstdio>
#include <queue>

namespace std {
    class Read {
        public:
        template<typename T>
        inline Read operator >> (T & u) {
            T sum = 0; short opt = 1;
            char ch = getchar();
            while(!isdigit(ch)) opt = (ch == '-') ? -1 : 1, ch = getchar();
            while( isdigit(ch)) sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
            u = sum * opt; return *this;
        }
    };
}
#define int long long
#define all(a) a.begin(), a.end()
#define endl "\n"
#define IO(u) freopen(u ".in", "r", stdin), freopen(u ".out", "w", stdout);

using namespace std; Read fin;

signed main() {
    #ifndef ONLINE_JUDGE
    IO("P15386")
    #endif

    int n; fin >> n;

    vector<vector<int> > dp(n + 1, vector<int>(2, 0));
    vector<vector<int> > G(n + 1, vector<int>());

    for (int i = 1, u, v; i <= n - 1; i ++ ) {
        fin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    function<void(int, int)> dfs = [&](int u, int fa) {
        int maxx1 = 0, maxx2 = 0, son = 0, sum = 0;

        if (G[u].size() == 1 && u != 1) {
            dp[u][0] = 1;
            dp[u][1] = 0;
            return;
        }

        if ((G[u].size() == 2 && u != 1) || (u == 1 && G[u].size() == 1)) {
            for (auto v : G[u]) {
                if (v != fa) {
                    dfs(v, u);
                    son = v;
                }
            }
        
            dp[u][0] = min(dp[son][0], dp[son][1]) + 1;
            dp[u][1] = min(dp[son][0], dp[son][1]);

            return;
        }

        for (auto v : G[u]) {
            if (v == fa)
                continue;
            
            dfs(v, u);
            sum += dp[v][0];

            int d = max(0ll, dp[v][0] - dp[v][1]);

            if (d > maxx2) {
                if (d > maxx1) {
                    maxx2 = maxx1;
                    maxx1 = d;
                } else {
                    maxx2 = d;
                }
            }
        }

        dp[u][0] = 1 + sum - maxx1 - maxx2;
        dp[u][1] = sum - maxx1;
    };

    dfs(1, 0);

    // for (int i = 0; i <= n; i ++ )
    //     cout << i << " " << dp[i][0] << " " << dp[i][1] << endl;

    cout << min(dp[1][1], dp[1][0] - 1);

    return 0;
}