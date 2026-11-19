/*
    @ Author:       Eric / Sky__White
    @ Filename:     CF559C.cpp
    @ Date:         20/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <functional>
#include <cctype>

namespace std {
    class Read {
    public:
        template<typename T>
        inline Read operator >> (T & x) {
            T sum = 0; short opt = 1;
            char ch = getchar();
            while (!isdigit(ch)) opt = (ch == '-') ? -1 : 1, ch = getchar();
            while (isdigit(ch)) sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
            x = sum * opt; return *this;
        }
    };
}
#define int long long
#define all(a) a.begin(), a.end()

using namespace std; Read fin;
using PII = pair<int, int>;

const int N = 2e5 + 10;
const int Mod = 1e9 + 7;

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % Mod;
        a = a * a % Mod;
        b >>= 1;
    }
    return res;
}

signed main() {
    int w, h, n; fin >> h >> w >> n; 

    vector<PII> arr(n + 1);
    for (int i = 1; i <= n; i ++ )
        fin >> arr[i].first >> arr[i].second;

    vector<int> fact(N + 1), invfact(N + 1); 
    fact[0] = 1;
    for (int i = 1; i <= N; i ++ )
        fact[i] = fact[i - 1] * i % Mod;
    invfact[N] = qpow(fact[N], Mod - 2);
    
    for (int i = N - 1; i >= 0; i -- )
        invfact[i] = invfact[i + 1] * (i + 1) % Mod;

    function<int(int, int)> C = [&](int n, int m) -> int {
        if (n < 0 || m < 0 || n < m) return 0; 
        return fact[n] * invfact[m] % Mod * invfact[n - m] % Mod;
    };

    arr.push_back({h, w});
    
    sort(arr.begin() + 1, arr.end());

    vector<int> dp(n + 2, 0);
    for (int i = 1; i <= n + 1; i ++ ) {
        int x = arr[i].first, y = arr[i].second;
        dp[i] = C(x + y - 2, x - 1);
        for (int j = 1; j < i; j++) {
            int xj = arr[j].first, yj = arr[j].second;
            if (x >= xj && y >= yj) {
                int sub = dp[j] * C(x - xj + y - yj, x - xj) % Mod;
                dp[i] = (dp[i] - sub + Mod) % Mod;
            }
        }
    }
    cout << dp[n + 1] << endl;
    return 0;
}