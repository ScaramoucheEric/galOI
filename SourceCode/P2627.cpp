/*
    @ Author:       Eric / Sky__White
    @ Filename:     P2627.cpp
    @ Date:         20/06/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <deque>

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
    int n, m; fin >> n >> m;

    vector<int> pre(n + 2);
    for (int i = 1; i <= n; i ++ )
    fin >> pre[i], pre[i] += pre[i - 1];

    // for (int i = 1; i <= n; i ++ )
    //     cout << pre[i] << " ";
    // cout << endl;

    vector<int> dp(n + 1), arr(1, 0); dp[1] = pre[1];
    deque<int> q; q.push_back(0);
    for (int i = 0; i <= n; i ++ ) {
        while(q.size() and i - q.front() > m)
            q.pop_front();

        // for (auto i : q)
        //     cout << i << " ";
        // cout << endl;
        // for (auto i : q)
        //     cout << arr[i] << " ";
        // cout << endl << dp[i - 1] << endl << endl;

        // cout << "RR: " << q.front() << endl;
        dp[i] = arr[q.front()] + pre[i];
        arr.push_back(dp[i] - pre[i + 1]);

        while(q.size() and arr[q.back()] <= arr.back())
            q.pop_back();
        q.push_back(arr.size() - 1);
    }

    // for (int i = 1; i <= n; i ++ )
    //     cout << dp[i] << " ";
    // cout << endl;

    cout << dp[n] << endl;

    return 0;
}