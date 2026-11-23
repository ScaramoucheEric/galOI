/*
    @ Author:       Eric / Sky__White
    @ Filename:     二维弹球.cpp
    @ Date:         30/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <list>
#include <deque>

namespace std {
    class Read {
        public:
        template<typename T>
        inline Read operator >> (T & x) {
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

using namespace std; Read fin;

signed main() {
    int n; fin >> n;
    vector<int> x(n);

    for (int i = 0; i < n; i ++ )
        fin >> x[i];
    
    vector<vector<vector<int> > > dp(1 << n + 1, vector<vector<int> >(n, vector<int>(n, 0))); // dp[S][i] 表示状态 S 下，第 i 个为第一个位置，第 j 个为第二个位置的最大值
    vector<int> res(n);

    for (int S = 1; S < (1 << n); S ++ ) {
        for (int i = 0; i < n; i ++ ) {
            if (~S & (1 << i)) continue;
            for (int j = 0; j < n; j ++ ) {
                if (~S & (1 << j)) continue;
                if (i == j) continue;
                if (dp[S][i][j] == 0) dp[S][i][j] = 2;
                for (int k = 0; k < n; k ++ ) {
                    if (S & (1 << k)) continue;
                    if (k == i or k == j) continue;
                    if (abs(x[i] - x[j]) * 2 <= abs(x[i] - x[k]))
                        dp[S | (1 << k)][k][i] = max(dp[S | (1 << k)][k][i], dp[S][i][j] + 1);
                    res[k] = max(res[k], dp[S | (1 << k)][k][i]);
                }
            }
        }
    }

    for (int i = 0; i < n; i ++ )
        cout << (res[i] ? res[i] : 2) << " ";
    cout << endl;

    // for (int S = 1; S < (1 << n); S ++ ) {
    //     for (int i = 0; i < n; i ++ ) {
    //         for (int j = 0; j < n; j ++ ) {
    //             bitset<12> b(S);

    //             cout << b.to_string() << " " << i << " " << j << " " << dp[S][i][j] << endl;
    //         }
    //     }
    // }
}