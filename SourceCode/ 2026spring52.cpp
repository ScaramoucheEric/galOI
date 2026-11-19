/*
    @ Author:       Eric / Sky__White
    @ Filename:      2026spring52.cpp
    @ Date:         03/31/2026
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

using namespace std; Read fin;

#define int long long
#define all(a) a.begin(), a.end()

const int INF = 0x3f3f3f3f3f3f3f3f;

signed main() {
    int n; fin >> n;
    vector<int> arr(n + 1);

    for (int i = 1; i <= n; i ++ )
        fin >> arr[i], arr.push_back(arr[i]);
    
    vector<int> presum(n + n + 1);

    for (int i = 1; i <= n + n; i ++ )
        presum[i] = presum[i - 1] + arr[i];
    
    vector<vector<int> > dp(n + n + 1, vector<int>(n + n + 1, INF));

    function<int(int,int)> dfs_min = [&](int l, int r) -> int {
        if (l == r) return dp[l][r] = 0;
        if (dp[l][r] != INF) return dp[l][r];

        for (int i = l; i < r; i ++ )
            dp[l][r] = min(dfs_min(l, i) + dfs_min(i + 1, r) + presum[r] - presum[l - 1], dp[l][r]);
        
        return dp[l][r];
    };

    int res = INF;

    for (int i = 1; i <= n; i ++ )
        cout << (res = min(res, dfs_min(i, i + n - 1))) << endl;

    cout << res << endl;

    dp.clear(), dp.resize(n + n + 1, vector<int>(n + n + 1, -INF));

    function<int(int,int)> dfs_max = [&](int l, int r) -> int {
        if (l == r) return dp[l][r] = 0;
        if (dp[l][r] != -INF) return dp[l][r];


        for (int i = l; i < r; i ++ )
            dp[l][r] = max(dfs_max(l, i) + dfs_max(i + 1, r) + presum[r] - presum[l - 1], dp[l][r]);
        
        return dp[l][r];
    };

    res = -INF;

    for (int i = 1; i <= n; i ++ )
        cout << (res = max(res, dfs_max(i, i + n - 1))) << endl;

    cout << res << endl;
}