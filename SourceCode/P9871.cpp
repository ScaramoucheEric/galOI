/*
    @ Author:       Eric / Sky__White
    @ Filename:     P9871.cpp
    @ Date:         20/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <cstdio>
#include <vector>

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

#define int long long
#define all(arr) arr.begin(), arr.end()

using namespace std; Read fin;

const int INF = 0x3f3f3f3f3f3f3f3f;
using PII = pair<int, int>;

void solve() {
    int n, m, K, d; fin >> n >> m >> K >> d;

    unordered_map<int, vector<PII> > chan;

    for (int i = 1; i <= m; i ++ ) {
        int r, len, v; fin >> r >> len >> v;
        chan[r].push_back({len, v});
    }

    vector<vector<int> > dp(n + 1, vector<int>(K + 1, -INF));
    dp[0][0] = 0;

    for (int i = 1; i <= n; i ++ ) {
        dp[i][0] = *max_element(all(dp[i - 1]));
        vector<PII> &vec = chan[i];
        for (int k = 1; k <= K and i - k >= 0; k ++ ) {
            dp[i][k] = dp[i - 1][k - 1] - d;
        }
        for (auto [len, v] : vec) {
            for (int k = len; k <= K and i - len >= 0; k ++ ) {
                dp[i][k] = dp[i][k] + v;
            }
        }
    }

    for (int i = 1; i <= n; i ++ ) {
        for (int j = 0; j <= K; j ++ )
            cout << dp[i][j] << " ";
        cout << endl;
    }

    for (int i = 1; i <= n; i ++ ) {
        cout << *max_element(all(dp[i])) << endl;
    }

    cout << (*max_element(all(dp[n]))) << endl;
}

signed main() {
    int T, c; fin >> c >> T;

    while(T -- ) {
        solve();
    }
}