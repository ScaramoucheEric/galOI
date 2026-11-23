/*
    @ Author:       Eric / Sky_Yue
    @ Filename:     P1171.cpp
    @ Time:         08/31/2025
    @ Email:        acwing@foxmail.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <functional>
#include <bitset>

using namespace std;

const int INF = 0x3f3f3f3f;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n; cin >> n;

    vector<vector<int> > G(n + 1, vector<int>(n + 1));

    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= n; j ++ )
            cin >> G[i][j];
    
    vector<vector<int> > dp(n, vector<int>(1 << n - 1, INF));

    for (int i = 0; i < n; i ++ )
        dp[i][0] = 0;
        
    for (int i = 2; i <= n; i ++ ) {
        dp[i - 1][1 << i - 2] = G[1][i];
    }
    
    for (int S = 0; S < 1 << n - 1; S ++ ) {
        vector<int> zero, one;
        
        for (int i = 0; i < n - 1; i ++ ) {
            if (S >> i & 1) one.push_back(i + 2);
            else zero.push_back(i + 2);
        }
        
        for (auto i : zero) {
            int s = S | (1 << i - 2);
            for (auto j : one) {
                dp[i - 1][s] = min(dp[i - 1][s], dp[j - 1][S] + G[j][i]);
            }
        }
    }

    int res = INF;

    for (int i = 0; i < n; i ++ )
        res = min(res, dp[i][(1 << n - 1) - 1] + G[i + 1][1]);

    cout << res << endl;

    return 0;
}