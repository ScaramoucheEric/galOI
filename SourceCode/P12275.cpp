/*
    @ Author:       Eric / Sky__White
    @ Filename:     P12275.cpp
    @ Date:         24/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <functional>
#include <set>

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

const int INF = 0x3f3f3f3f3f3f3f3f;

signed main() {
    int n, m; fin >> n >> m;
    
    vector<int> a(n + 1);

    for (int i = 1; i <= n; i ++ )
        fin >> a[i];

    struct Node {
        int x, y, k, w;

        bool operator < (const Node & W) const {
            return y < W.y;
        }
    }; vector<Node> w(m + 1);

    for (int i = 1; i <= m; i ++ ) {
        fin >> w[i].x >> w[i].y >> w[i].k >> w[i].w;
    }

    sort(1 + all(w));

    vector<double> f(n + 1);

    for (int i = 1; i <= m; i ++ ) {
        auto [x, y, k, W] = w[i];
        if (k == 0) {
            f[y] = max((double)W, f[y]);
        } else {
            f[y] = max(1.0 * W / (k / f[x] + 1.0), f[y]);
        }
    }

    double res = 0;

    for (int i = 1; i <= n; i ++ )
        res = max(res, f[i] * a[i]);

    printf("%.2lf\n", res);

    return 0;
}