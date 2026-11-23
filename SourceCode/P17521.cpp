#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <functional>
#include <cstdio>
#include <map>
#include <vector>

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
#define IO(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout);
#define endl "\n"

using namespace std; Read fin;

const int INF = 0x3f3f3f3f3f3f3f3f;

signed main() {
    int n, s; fin >> n >> s;

    struct Ball {
        int w, x;
        bool operator<(const Ball &a) const {
            if (w != a.w) {
                return w < a.w;
            }
            return x < a.x;
        }
    }; vector<Ball> b(n + 1);

    for (int i = 1; i <= n; i ++ ) {
        fin >> b[i].w;
    }
    for (int i = 1; i <= n; i ++ ) {
        fin >> b[i].x;
    }
    
    sort(1 + all(b));

    vector<vector<vector<int> > > dp(2, vector<vector<int> > (s + 1, vector<int>(n + 1)));
    
    for (int i = 0; i < 2; i ++ ) {
        for (int j = 0; j <= s; j ++ ) {
            for (int k = 0; k <= n; k ++ ) {
                dp[i][j][k] = -INF;
            }
        }
    }
    
    dp[0][0][0] = 0;
    
    for (int i = 1; i <= n; i ++ ) {
        int w = b[i].w;
        int x = b[i].x;
        int index = i & 1;
        
        for (int j = 0; j <= s; j ++ ) {
            dp[index][j][0] = -INF;
            for (int p = 0; p <= min(w - b[i - 1].w, n); p ++ ) {
                dp[index][j][0] = max(dp[index][j][0], dp[1 - index][j][p]);
            }
            dp[index][j][1] = -INF;
            int p = w + 1 - b[i - 1].w;
            if (p >= 0 && p <= n) {
                dp[index][j][1] = max(dp[index][j][1], dp[1 - index][j][p]);
            }
            p = min(w - b[i - 1].w, n);
            if (j >= x) {
                for (int k = 0; k <= p; k ++ ) {
                    dp[index][j][1] = max(dp[index][j][1], dp[1 - index][j - x][k] + w);
                }
            }
            
            for (int k = 2; k <= n; k ++ ) {
                dp[index][j][k] = -INF;
                p = w + k - b[i - 1].w;
                if (p >= 0 && p <= n) {
                    dp[index][j][k] = max(dp[index][j][k], dp[1 - index][j][p]);
                }
                p = w + k - 1 - b[i - 1].w;
                if (p >= 0 && p <= n && j >= x) {
                    dp[index][j][k] = max(dp[index][j][k], dp[1 - index][j - x][p] + w + k - 1);
                }
            }
        }
    }
    
    int ans = 0;
    for (int j = 0; j <= s; j ++ ) {
        for (int k = 0; k <= n; k ++ ) {
            ans = max(ans, dp[n & 1][j][k]);
        }
    }
    
    cout << ans << endl;

    return 0;
}
