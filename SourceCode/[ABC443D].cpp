/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC443D].cpp
    @ Time:         01/31/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

namespace std {
    class Read {
    public:
        template<typename T>
        inline Read& operator>>(T& x) {
            T sum = 0, opt = 1;
            char ch = getchar();
            while (!isdigit(ch)) opt = (ch == '-') ? -1 : 1, ch = getchar();
            while (isdigit(ch)) sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
            x = sum * opt;
            return *this;
        }
    } fin;
}

#define int long long

using namespace std;

void solve() {
    int n;
    fin >> n;
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) fin >> a[i];
    
    b[1] = a[1];
    for (int i = 2; i <= n; i++) {
        b[i] = min(a[i], b[i - 1] + 1);
    }
    
    for (int i = n - 1; i >= 1; i--) {
        b[i] = min(b[i], b[i + 1] + 1);
    }
    
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += a[i] - b[i];
    }
    cout << ans << '\n';

    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= m; j ++ ) {
            if (dp[i][j] == dp[i - 1][j - 1] and dp[i][j] == dp[i - 1][j])
                return ;
            int t = *max_element(all(dp[i - 1][j - 1]));
            int mt = *min_element(all(dp[i - 1][j - 1]));

            int dlt = mt - t;
            dp[i][j][1] += abs(dlt - dp[i - 1][j - 1][1]);
            dp[i][j][2] -= abs(dlt - dp[i - 1][j - 1][2]);
            dp[i][j][3] = abs(dlt - dp[i - 1][j - 1][2]);

            
        }

    return ;
}

signed main() {
    int T;
    fin >> T;
    while (T--) {
        solve();
    }
    return 0;
}