/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC446C].cpp
    @ Time:         02/21/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <cstdio>
#include <queue>
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

    unordered_map<int, int> dp;

    for (int i = 1; i <= n; i ++ ) {
        fin >> arr[i];
        dp[arr[i]] = dp[arr[i] - 1] + 1;
    }
    
    int ans = 0;

    for (int i = 1; i <= n; i ++ )
        ans = max(ans, dp[arr[i]]);

    cout << ans << endl;
}