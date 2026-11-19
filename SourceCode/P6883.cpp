#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <functional>

using namespace std;

#define int long long

const int INF = 0x3f3f3f3f3f3f3f3f;

signed main() {
    int n, m; cin >> n >> m;
    
    vector<vector<int> > arr(n, vector<int>(n));

    for (int i = 0; i < n; i ++ )
        for (int j = 0; j < n; j ++ )
            cin >> arr[i][j];
        
    int mask = 1 << n; mask -- ;

    vector<int> dp(1 << n, INF);

    dp[mask] = 0;
    int res = INF;

    for (int S = mask; S; S -- ) {
        vector<int> one;
        for (int i = 0; i < n; i ++ ) {
            if (S >> i & 1)
                one.push_back(i);
        }
        
        for (auto a : one) {
            int s = S - (1 << a);
            for (auto b : one) {
                if (a == b) continue;
                dp[s] = min(dp[s], dp[S] + arr[a][b]);
            }
        }

        if (one.size() <= m) {
            res = min(res, dp[S]);
        }
    }
    
    // for (int i = 0; i < 1 << n; i ++ )
    //     cout << bitset<6>(i) << " " << dp[i] << endl;

    cout << res << endl;

    return 0;
}