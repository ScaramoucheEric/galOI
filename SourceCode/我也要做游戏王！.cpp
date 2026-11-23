/*
    @ Author:       Eric / Sky__White
    @ Filename:     我也要做游戏王！.cpp
    @ Date:         20/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <vector>
#include <unordered_map>

namespace std {
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
}
#define int long long
#define uint unsigned long long
#define all(a) a.begin(), a.end()

using namespace std; Read fin;

const int Mod = 1e9 + 7;

int qpow(int a, int b) {
    int r = 1;
    while(b) {
        if(b & 1) r = r * a % Mod;
        a = a * a % Mod;
        b >>= 1;
    }
    return r;
}

signed main() {
    freopen("Magnet.in", "r", stdin);
    freopen("Magnet.out", "w", stdout);
    
    int n, l; fin >> n >> l;

    vector<int> r(n);

    for(int i = 0; i < n; i ++ )
        fin >> r[i];

    sort(all(r));

    int K = l - 1;
    vector<vector<int>> dp(n + 1, vector<int>(K + 1, 0));
    if(n >= 1) dp[1][0] = 1;

    for(int i = 2; i <= n; i ++ ) {
        vector<vector<int>> ndp(n + 1, vector<int>(K + 1, 0));
        int ri = r[i - 1];
        for(int j = 1; j < i; j ++ ) {
            for(int k = 0; k <= K; k ++ ) {
                int val = dp[j][k];
                if(!val) continue;

                if(k + ri <= K) {
                    int add = 2 * j % Mod * val % Mod;
                    ndp[j][k + ri] = (ndp[j][k + ri] + add) % Mod;
                }
                if(j + 1 <= n) {
                    ndp[j + 1][k] = (ndp[j + 1][k] + val) % Mod;
                }
                if(j >= 2 && k + 2 * ri <= K) {
                    int tt = j * (j - 1) % Mod;
                    ndp[j - 1][k + 2 * ri] = (ndp[j - 1][k + 2 * ri] + val * tt) % Mod;
                }
            }
        }

        // for (int j = 1; j <= n; j ++ )
        //     for (int k = 0; k <= K; k ++ )
        //         cout << ndp[j][k] << " \n"[k == K];

        dp.swap(ndp);
    }

    int maxN = l + n + 5;

    vector<int> fact(maxN + 1), invfact(maxN + 1);
    fact[0] = 1;
    
    for(int i = 1; i <= maxN; i ++ ) fact[i] = fact[i - 1] * i % Mod;
    
    invfact[maxN] = qpow(fact[maxN], Mod - 2);
    for(int i = maxN; i >= 1; i -- ) invfact[i - 1] = invfact[i] * i % Mod;

    function<int(int,int)> C = [&](int N, int M) -> int {
        if(M < 0 || M > N) return 0;
        return fact[N] * invfact[M] % Mod * invfact[N - M] % Mod;
    };

    int ans = 0;

    for(int k = 0; k <= K; k ++ ) {
        if(dp[1][k] == 0) continue;

        int tt = C(l - 1 - k + n, n);
        
        ans = (ans + dp[1][k] * tt) % Mod;
    }

    cout << ans << endl;

    return 0;
}