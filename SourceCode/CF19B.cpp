/*
    @ Author:       Eric / Sky__White
    @ Filename:     CF19B.cpp
    @ Date:         20/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/
#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <cstdio>
#include <vector>

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

#define int long long
#define all(arr) arr.begin(), arr.end()

using namespace std; Read fin;

const int INF = 0x3f3f3f3f3f3f3f3f;

signed main() {
    int n; fin >> n;

    vector<int> arr(n + 1), t = arr;
    
    int m = 0;
    
    for (int i = 1; i <= n; i ++ ) {
        fin >> t[i] >> arr[i];
        t[i] ++ ; m = max(m, t[i]);
    }
    m += n;
    vector<int> dp(m + 1, INF);

    dp[0] = 0;

    for (int i = 1; i <= n; i ++ )
        for (int j = m; j >= t[i]; j -- )
            dp[j] = min(dp[j], dp[j - t[i]] + arr[i]);

    cout << (*min_element(n + all(dp))) << endl;

    return 0;
}