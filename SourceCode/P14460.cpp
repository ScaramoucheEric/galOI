/*
    @ Author:       Eric / Sky__White
    @ Filename:     P14460.cpp
    @ Date:         21/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <functional>
#include <vector>
#include <queue>
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

const int INF = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int m, k, t1, t2; fin >> m >> k >> t1 >> t2;

    vector<int> dp(m + 1, INF);

    dp[0] = 0;

    if (t1 <= t2) {
        for (int i = 1; i <= m; i ++ )
            dp[i] = i * k + i * t1, cout << dp[i] << " ";
        cout << endl;
        return ;
    }


    vector<int> q(m + 1); int f = 0;

    for (int i = 1; i <= m; i ++ ) {
        while(f < i - 1 and q[f + 1] <= i * k + (t1 - t2)) {
            f ++ ;
        }
        dp[i] = max(q[f], k * i) + f * t2 + (i - f) * t1;
        q[i] = i * t2 + dp[i];
    }

    for (int i = 1; i <= m; i ++ )
        cout << dp[i] << " \n"[i == m];
}

signed main() {
    int T; fin >> T;

    while(T -- ) {
        solve();
    }
}

// dp[i] - i * t1 = dp[j] + j * t2 + j * (t2 - t1)
// dp[i] - i * t1 - i * k = j * (t2 - t1)