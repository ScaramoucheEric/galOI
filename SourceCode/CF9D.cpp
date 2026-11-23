/*
	@ Author:       Eric / Sky__White
	@ Filename:     CF9D.cpp
	@ Date:         20/07/2026
	@ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <vector>

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
#define all(arr) arr.begin(), arr.end()

using namespace std; Read fin;

signed main() {
	int n, h; fin >> n >> h;
	
	vector<vector<int> > dp(n + 1, vector<int>(n + 1));
	
	for(int i = 0; i <= n; i ++ )
		dp[0][i] = 1;

	for(int i = 1; i <= n; i ++ )
		for(int j = 1; j <= n; j ++ )
			for(int k = 0; k < j; k ++ )
				dp[j][i] += dp[k][i - 1] * dp[j - k - 1][i - 1];

	cout << dp[n][n] - dp[n][h - 1] << endl;
				
	return 0;
}
