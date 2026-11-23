/*
    @ Author:       Eric / Sky__White
    @ Filename:     BD202329.cpp
    @ Time:         02/14/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <priority_queue>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

#define int long long

const int MOD = 1e9 + 7;
const int MAXN = 105;

int C[MAXN * 2][MAXN * 2];
int fact[MAXN];
int dp[MAXN][MAXN][MAXN];

using PII = pair<int, int> ;

signed main() {
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    cout << N << endl;
    
    for (int i = 0; i < MAXN * 2; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) {
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % MOD;
        }
    }

    priority_queue<PII, vector<PII>, greater<PII> > q;
    
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = fact[i-1] * i % MOD;
    }
    
    vector<int> cnt(N + 1, 0);
    for (int d = 0; d <= N; d++) {
        for (int i = 0; i < N; i++) {
            if (A[i] >= d) cnt[d]++;
        }
    }
    
    memset(dp, 0, sizeof(dp));
    dp[0][1][1] = 1;
    
    for (int d = 0; d < N; d++) {
        for (int used = 1; used <= N; used++) {
            for (int k = 1; k <= used; k++) {
                if (dp[d][used][k] == 0) continue;
                
                int remain = cnt[d+1] - used;
                if (remain < 0) continue;
                
                for (int t = 0; t <= remain; t++) {
                    if (used + t > N) continue;
                    
                    int ways = C[t + k - 1][k - 1] * fact[t] % MOD;
                    
                    ways = ways * C[remain][t] % MOD;
                    
                    dp[d+1][used + t][t] = (dp[d+1][used + t][t] + dp[d][used][k] * ways) % MOD;
                }
            }
        }
    }
    
    int ans = 0;
    for (int k = 1; k <= N; k++) {
        ans = (ans + dp[N][N][k]) % MOD;
    }

    for (int i = 0; i <= N; i ++ ) {
        for (int j = 0; j <= N; j ++ )
            for (int k = 0; k <= N; k ++ )
                printf("dp[%lld][%lld][%lld] = %lld\n", i, j, k, dp[i][j][k]);
    }
    
    cout << ans << endl;
    
    return 0;
}