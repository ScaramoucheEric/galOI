/*
    @ Author:       Eric / Sky__White
    @ Filename:     CF1762D.cpp
    @ Date:         27/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>

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
#define all(a) a.begin(), a.end()

using namespace std; Read fin;

int query(int i, int j) {
    cout << "? " << i << " " << j << endl;

    int r; cin >> r;
    
    if (r == -1) exit(0);

    return r;
}

void solve() {
    int n; cin >> n;

    if (n == -1) exit(0);

    int u = 1, v = 2;
    
    for (int w = 3; w <= n; w ++ ) {
        int gu = query(u, w);
        int gv = query(v, w);
        if (gu < gv) u = w;
        else if (gv < gu) v = w;
    }

    cout << "! " << u << " " << v << endl;
    int ver; cin >> ver;

    if (ver == -1) exit(0);
}

signed main() {
    int T; cin >> T;

    while (T -- ) solve();
    return 0;
}