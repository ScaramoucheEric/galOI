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

#define all(a) a.begin(), a.end()
#define int long long

using namespace std; Read fin;

signed main() {
    // freopen("way.in", "r", stdin);
    // freopen("way.out", "w", stdout);

    int m, n; fin >> m >> n;

    vector<int> w(n + 1), t(n + 1);
    vector<vector<int> > dp(n + 1, vector<int>(m + 1));

    for (int i = 1; i <= n; i ++ )
        fin >> t[i] >> w[i];

    for (int i = 1; i <= n; i ++ ) {
        for (int j = 0; j < t[i]; j ++ )
            dp[i][j] = dp[i - 1][j];
        for (int j = t[i]; j <= m; j ++ ) {
            dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - t[i]] + w[i]);
        }
    }

    vector<int> cur;
    vector<vector<int> > res;
    function<void(int, int)> dfs = [&](int i, int j) -> void {
        // cout << i << endl;
        if (i == 1) {
            if (dp[i][j] != 0)
                cur.push_back(1);
            res.push_back(cur);
            if (dp[i][j] != 0)
                cur.pop_back();
            return ;
        }
        if (dp[i][j] == dp[i - 1][j - t[i]] + w[i]) {
            cur.push_back(i);
            dfs(i - 1, j - t[i]);
        } else if (dp[i][j] == dp[i - 1][j]) {
            dfs(i - 1, j);
        }
        cur.pop_back();
    };
    
    dfs(n, m);

    for (auto &i : res)
        reverse(all(i));
    
    sort(all(res));
    
    int opt; fin >> opt;
    
    cout << dp[n][m] << endl;
    
    // cout << res.size() << endl;

    if (opt)
        for (int i : res[0])
            cout << i << " ";
}