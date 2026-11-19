/*
    @ Author:       Eric / Sky__White
    @ Filename:     CF1854B.cpp
    @ Date:         21/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <functional>
#include <bitset>

namespace std {
    class Read {
    public:
        template<typename T>
        inline Read operator >> (T & x) {
            T sum = 0; short opt = 1;
            char ch = getchar();
            while (!isdigit(ch)) opt = (ch == '-') ? -1 : 1, ch = getchar();
            while (isdigit(ch)) sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
            x = sum * opt; return *this;
        }
    };
}
#define int long long
#define all(a) a.begin(), a.end()

using namespace std; Read fin;

const int N = 200000;
bitset<N> dp, res;

signed main() {
    int n; fin >> n;

    vector<int> pre(n + n + 1), arr(n + 1);

    for (int i = 1; i <= n; i ++ ) {
        fin >> arr[i]; pre[i] = pre[i - 1] + arr[i];
    }

    dp[1] = 1;

    for (int i = 1; i <= n; i ++ ) {
        dp |= dp << arr[i];
        res[i] = dp[i];
        dp[i] = 0;
    }

    for (int i = n + 1; i <= n + n; i ++ ) {
        res[i] = dp[i];
        pre[i] = pre[i - 1];
    }

    int ans = 0;

    for (int i = 1; i <= n + n; i ++ )
        if (res[i])
            ans = max(ans, pre[i] - i + 1);

    cout << ans << endl;

    return 0;            
}