/*
    @ Author:       Eric / Sky__White
    @ Filename:     P2182.cpp
    @ Time:         01/20/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <functional>
#include <bitset>

namespace std {
    class Read {
        public:
            template<typename T>
            inline Read operator >> (T & x) {
                T sum = 0, opt = 1;
                char ch = getchar();
                while(!isdigit(ch)) opt = (ch == '-') ? -1 : 1, ch = getchar();
                while( isdigit(ch)) sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
                x = sum * opt; return (*this);
            }
    };
}
#define int long long
#define all(a) a.begin(), a.end()

using namespace std; Read fin;

const int Mod = 1e9 + 7;

vector<vector<int> > C, dp;

void Init_C(int n) {
    for (int i = 0; i <= n; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) {
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % Mod;
        }
    }
}

signed main() {
    int n, k, m; fin >> n >> k >> m;
    
    string s1, s2;
    cin >> s1 >> s2;
    
    int diff = 0;
    for (int i = 0; i < n; i++) {
        if (s1[i] != s2[i]) diff++;
    }

    C.resize(n + 1, vector<int>(n + 1));
    
    Init_C(n);
    
    dp.resize(k + 1, vector<int>(n + 1));
    dp[0][diff] = 1;
    
    for (int i = 0; i < k; i++) {
        for (int j = 0; j <= n; j++) {
            if (dp[i][j] == 0) continue;
            for (int x = 0; x <= j; x++) {
                if (m - x < 0 or m - x > n - j) continue;

                int j2 = j - x + (m - x);
                if (j2 < 0 or j2 > n) continue;

                int ways = (C[j][x] * C[n - j][m - x]) % Mod;

                dp[i + 1][j2] = (dp[i + 1][j2] + dp[i][j] * ways) % Mod;
            }
        }
    }
    
    cout << dp[k][0] << endl;

    
    
    return 0;
}