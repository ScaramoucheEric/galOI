/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC484D].cpp
    @ Date:         14/11/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <functional>
#include <queue>

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
#define endl "\n"
#define IO(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout);

using namespace std; Read fin;

signed main() {
    int n; fin >> n;

    vector<int> arr(n);

    for (int i = 0; i < n; i ++ ) {
        fin >> arr[i];
    }

    int ans = 1; 
    
    vector<int> cnt(n + 1, 0);

    for (int i = 0; i < n; i ++ ) {
        if (i == n - 1 or arr[i] != arr[i + 1]) {
            ans += i - cnt[arr[i]];
        }
        cnt[arr[i]] ++ ;
    }

    cout << ans << endl;

    return 0;
}