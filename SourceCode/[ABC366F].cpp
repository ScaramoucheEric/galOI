/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC366F].cpp
    @ Time:         11/21/2025
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <functional>

using namespace std;

#define all(a) a.begin(), a.end()
#define int long long

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
    } fin;
}

struct Node {
    int a, b;
    bool operator < (const Node & W) const {
        return a * W.b + b < W.a * b + W.b;
    }
};

signed main() {
    int n, k; fin >> n >> k;
    
    vector<Node> arr(n + 1);

    for (int i = 1; i <= n; i ++ ) {
        fin >> arr[i].a >> arr[i].b;
    }

    sort(1 + all(arr));

    // for (int i = 1; i <= n; i ++ ) {
    //     cout << arr[i].a << " " << arr[i].b << endl;
    // }

    vector<vector<int> > dp(n + 1, vector<int>(k + 1, 0));

    for (int i = 0; i <= n; i ++ )
        dp[i][0] = 1;

    for (int i = 1; i <= n; i ++ ) {
        for (int j = 1; j <= k; j ++ ) {
            dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] * arr[i].a + arr[i].b);
        }
    }

    cout << dp[n][k] << endl;
}