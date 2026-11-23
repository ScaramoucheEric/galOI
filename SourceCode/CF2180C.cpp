/*
    @ Author:       Eric / Sky__White
    @ Filename:     CF2180C.cpp
    @ Date:         11/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <cstdio>
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

const int Mod = 1e9 + 7;
const int INF = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int n, k; fin >> n >> k;

    if (k & 1) {
        for (int i = 1; i <= k; i ++ )
            cout << n << " \n"[i == k];
        return ;
    }

    vector<int> a(k, 0);

    int pos = 0;
    vector<int> bit;
    while(n) {
        bit.push_back(n & 1);
        n >>= 1;
    }

    for (int i = bit.size() - 1; ~i; i -- ) {
        if (bit[i]) {
            for (int j = 0; j < k; j ++ )
                if (pos % k != j)
                    a[j] += (1 << i);
            pos ++ ;
        } else {
            for (int j = 1; j < min(pos, k); j += 2) {
                a[j] += 1 << i;
                a[j - 1] += 1 << i;
            }
        }
    }

    for (int i = 0; i < k; i ++ ) {
        cout << a[i] << " \n"[i == k - 1];
    }

    return ;
}

signed main() {
    int T; fin >> T;

    while(T -- ) {
        solve();
    }

    return 0;
}