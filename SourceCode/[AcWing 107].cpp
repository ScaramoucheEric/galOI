/*
    @ Author:       Eric / Sky__White
    @ Filename:     [AcWing 107].cpp
    @ Time:         11/28/2025
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <functional>

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
    } fin;
}
#define int long long
#define all(a) a.begin(), a.end()

using namespace std;

signed main() {
    int n; 
    fin >> n;
    while(n) {
        vector<int> arr(n + 1);
        for (int i = 1; i <= n; i ++ )
            fin >> arr[i];
        
        function<int(int, int)> dfs = [&](int l, int r) -> int {
            if (l == r) return 0;
            int mid = l + r >> 1;
            int res = dfs(l, mid) + dfs(mid + 1, r);
            
            vector<int> b(r - l + 1);
            b.swap(arr);
            int pos1 = l, pos2 = mid + 1, pos = 0;

            while(pos1 <= mid and pos2 <= r) {
                if (b[pos1] <= b[pos2]) arr[pos ++ ] = b[pos1 ++ ];
                else /* (b[pos2] >  b[pos2]) */ arr[pos ++ ] = b[pos2 ++ ], res += mid - pos1 + 1;
            }
            while(pos1 <= mid) arr[pos ++ ] = b[pos1 ++ ];
            while(pos2 <= r) arr[pos ++ ] = b[pos2 ++ ];
            
            b.swap(arr);
            
            for (int i = 0; i < r - l + 1; i ++ )
                arr[i + l] = b[i];

            return res;
        };
        printf("%lld\n", dfs(1, n));
        fin >> n;
    }
}