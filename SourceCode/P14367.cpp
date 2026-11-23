/*
    @ Author:       Eric / Sky__White
    @ Filename:     P14367.cpp
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

const int Mod = 1e9 + 7;

signed main() {
    int n, m; fin >> n >> m;

    struct Node {
        int num;

        int operator +(const int & W) {
            return (num + W) % Mod;
        }
        int operator *(const int & W) {
            return (num * W) % Mod;
        }
        Node& operator =(const int & W) {
            num = W;
            return *this;
        }
        Node& operator +=(const int & W) {
            (num += W) %= Mod;
            return *this;
        }
        Node& operator *=(const int & W) {
            (num *= W) %= Mod;
            return *this;
        }
    };

    vector<vector<Node> > dp(n + 1, vector<Node>(m + 1));

    for (int i = 0; i <= n; i ++ ) dp[i][0] = 1;
    for (int i = 0; i <= m; i ++ ) dp[0][i] = 1;

    for (int i = 1; i <= n; i ++ ) {
        for (int j = 1; j <= m; j ++ ) {
            dp[i][j] = dp[i - 1][j];
            dp[i][j] += dp[i - 1][j - 1] * 4 * j;
            if (j > 1)
                dp[i][j] += dp[i - 1][j - 2] * (j * (j - 1) / 2);
            if (i > 1)
                dp[i][j] += dp[i - 2][j - 1] * (i - 1) * j;
        }
    }

    cout << dp[n][m].num - 1 << endl;
}