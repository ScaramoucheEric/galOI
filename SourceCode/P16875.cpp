#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <cstdio>
#include <queue>

namespace std {
    class Read {
        public:
        template<typename T>
        inline Read operator >> (T & u) {
            T sum = 0; short opt = 1;
            char ch = getchar();
            while(!isdigit(ch)) opt = (ch == '-') ? -1 : 1, ch = getchar();
            while( isdigit(ch)) sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
            u = sum * opt; return *this;
        }
    };
}
#define int long long
#define all(a) a.begin(), a.end()
#define endl "\n"
#define IO(u) freopen(u ".in", "r", stdin), freopen(u ".out", "w", stdout);

using namespace std; Read fin;

const int INF = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int n, m; fin >> n >> m;
    
    vector<int> arr(n + 1);

    for (int i = 1; i <= n; i ++ ) {
        fin >> arr[i];
    }

    vector<vector<vector<int> > > dp(n + 1, vector<vector<int> >(n + 1, vector<int>(2, INF)));

    function<int(int, int)> dist = [&](int a, int b) -> int {
        return min(abs(a - b), m - abs(a - b));
    };

    for (int len = 1; len <= n; len ++ ) {
        for (int l = 1; l + len - 1 <= n; l ++ ) {
            int r = l + len - 1;
            if (l == r) dp[l][r][1] = dp[l][r][0] = 0;
            else {
                dp[l][r][0] = min({dp[l][r][0], dp[l + 1][r][1] + dist(arr[l], arr[r]),
                                                dp[l + 1][r][0] + dist(arr[l], arr[l + 1])});
                dp[l][r][1] = min({dp[l][r][1], dp[l][r - 1][0] + dist(arr[l], arr[r]),
                                                dp[l][r - 1][1] + dist(arr[r - 1], arr[r])});
            }
        }
    }

    // for (int i = 1; i <= n; i ++ ) {
    //     for (int j = i; j <= n; j ++ ) 
    //         cout << i << " " << j << " " << dp[i][j][0] << " " << dp[i][j][1] << endl;
    // }

    cout << min(dp[1][n][0] + dist(arr[1], 0), dp[1][n][1] + dist(arr[n], 0)) << endl;
}

signed main() {
    #ifndef ONLINE_JUDGE
    IO("P16875")
    #endif

    int T; fin >> T;

    for (int C = 1; C <= T; C ++ ) {
        cout << "Case #" << C << ": ";
        solve();
    }
}