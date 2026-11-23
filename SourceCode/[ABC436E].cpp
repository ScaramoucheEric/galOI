/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC436E].cpp
    @ Time:         12/13/2025
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

using namespace std; Read fin;

signed main() {
    int n;
    fin >> n;
    
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        fin >> p[i];
        p[i]--;
    }
    
    vector<bool> vis(n, false);
    int ans = 0;
    
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            int cur = i, len = 0;
            
            while (!vis[cur]) {
                vis[cur] = true;
                cur = p[cur];
                len++;
            }
            
            // for (int i = 1; i <= n; i ++ )
            //     printf("%3lld ", i);
            // cout << endl;
            // for (int i = 0; i < n; i ++ )
            //     printf("%3lld ", (signed)vis[i]);
            // cout << endl;
            // cout << len << endl << endl;
            ans += (int)len * (len - 1) / 2;
        }
    }
    
    // cout << endl;
    cout << ans << endl;
    
    return 0;
}