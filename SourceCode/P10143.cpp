/*
    @ Author:       Eric / Sky__White
    @ Filename:     P10143.cpp
    @ Date:         13/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
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

const int Mod = 998244353;

signed main() {
    int c, n, T; fin >> c >> n >> T;

    vector<int> score(n + 1), t(n + 1), pre(n + 1);

    for (int i = 1; i <= n; i ++ ) {
        fin >> score[i];
    }
    for (int i = 1; i <= n; i ++ ) {
        fin >> t[i]; pre[i] = pre[i - 1] + t[i];
    }

    vector<int> pow2(n + 1); pow2[0] = 1;

    for (int i = 1; i <= n; i ++ ) pow2[i] = (pow2[i - 1] << 1) % Mod;

    int res = 0;
    vector<int> dp(T + 1); dp[0] = 1;
    for (int i = 1; i <= n; i ++ ) {
        int sum = 0;
        for (int j = 0; j <= T - t[i]; j ++ ) (sum += dp[j]) %= Mod;
        (res += sum * pow2[n - i] % Mod * score[i]) %= Mod;
        for (int j = T; j >= t[i]; j -- ) (dp[j] += dp[j - t[i]]) %= Mod;
    }

    dp.clear(); dp.resize(T + 1); dp[0] = 1;
    // for (int i = 1; i <= n; i ++ )
    //     cout << dp[i] << " \n"[i == n];

    for (int i = n; i; i -- ) {
        int sum = 0;
        for (int j = 0; j <= T - pre[i]; j ++ ) (sum += dp[j]) %= Mod;
        (res += sum * pow2[i - 1] % Mod * score[i]) %= Mod;
        for (int j = T; j >= t[i]; j -- ) (dp[j] += dp[j - t[i]]) %= Mod;
    }

    cout << res << endl;
}