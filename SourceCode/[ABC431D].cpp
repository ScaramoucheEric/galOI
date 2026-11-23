/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC431D].cpp
    @ Time:         11/08/2025
    @ Email:        acwing@foxmail.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

#define int long long
#define all(a) a.begin(), a.end();

const int INF = 1e18;

signed main() {
    int n;
    cin >> n;
    vector<int> w(n), h(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> h[i] >> b[i];
    }

    int m = 0;
    for (int wei : w) m += wei;
    int max_m = m / 2;

    vector<int> dp(max_m + 1, -INF);
    dp[0] = 0;

    for (int i = 0; i < n; i++) {
        for (int wei = 0; wei <= max_m; wei++) {
            if (dp[wei] != -INF) {
                dp[wei] += b[i];
            }
        }
        for (int wei = max_m - w[i]; wei >= 0; wei--) {
            if (dp[wei] != -INF) {
                dp[wei + w[i]] = max(dp[wei + w[i]], dp[wei] - b[i] + h[i]);
            }
        }
    }

    int ans = 0;
    for (int wei = 0; wei <= max_m; wei++) {
        ans = max(ans, dp[wei]);
    }
    cout << ans << endl;

    return 0;
}