#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

const int MOD = 998244353;

int main() {
    int X1, X2, X3;
    cin >> X1 >> X2 >> X3;
    
    vector<vector<long long>> dp(X2 + 1, vector<long long>(3, 0));
    dp[0][1] = 1;
    
    for (int i = 0; i < X1 + X2 + X3; i++) {
        vector<vector<long long>> ndp(X2 + 1, vector<long long>(3, 0));
        for (int x2 = 0; x2 <= X2; x2++) {
            for (int last = 0; last < 3; last++) {
                if (dp[x2][last] == 0) continue;
                long long val = dp[x2][last];
                
                if (last == 0) {
                    if (x2 < X2) ndp[x2 + 1][1] = (ndp[x2 + 1][1] + val) % MOD;
                    ndp[x2][0] = (ndp[x2][0] + val) % MOD;
                } else if (last == 1) {
                    ndp[x2][1] = (ndp[x2][1] + val) % MOD;
                    if (x2 < X2) ndp[x2 + 1][1] = (ndp[x2 + 1][1] + val) % MOD;
                } else if (last == 2) {
                    if (x2 < X2) ndp[x2 + 1][1] = (ndp[x2 + 1][1] + val) % MOD;
                    ndp[x2][2] = (ndp[x2][2] + val) % MOD;
                }
            }
        }
        dp = ndp;

        for (auto i : dp) {
            for (auto j : i)
                cout << j << " ";
            cout << endl;
        }
    }
    
    long long ans = (dp[X2][0] + dp[X2][1] + dp[X2][2]) % MOD;
    cout << ans << endl;
    
    return 0;
}