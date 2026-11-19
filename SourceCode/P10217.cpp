/*
    @ Author:       Eric / Sky__White
    @ Filename:     P10217.cpp
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

int down(int a, int b) {
    int q = a / b, r = a % b;
    if (r != 0 && ((r ^ b) < 0)) q -- ;
    return q;
}

int up(int a, int b) {
    return -down(-a, b);
}

void solve() {
    int n, k, x, y; fin >> n >> k >> x >> y;

    vector<int> X(n), Y(n);
    int dirs[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    int sumd[4] = {0, 0, 0, 0};
    int posd[4];

    for (int d = 0; d < 4; d ++ )
        posd[d] = dirs[d][0] * x + dirs[d][1] * y;

    for (int i = 0; i < n; i ++ ) {
        fin >> X[i] >> Y[i];
        for (int d = 0; d < 4; d ++ )
            sumd[d] += dirs[d][0] * X[i] + dirs[d][1] * Y[i] + k;
    }

    const int INF = 0x3f3f3f3f3f3f3f3f;
    int cur[4] = {0, 0, 0, 0};
    int ans = INF;

    for (int i = 0; i < n; i ++ ) {
        int L = 0, R = INF;
        bool ok = true;
        for (int d = 0; d < 4; d ++ ) {     
            int tt = posd[d] - cur[d];
            int Sd = sumd[d];
            if (Sd == 0) {
                if (tt > 0) { ok = false; break; }
            } else if (Sd > 0) {
                int lb = up(tt, Sd);
                if (lb > L) L = lb;
            } else {
                int ub = down(tt, Sd);
                if (ub < R) R = ub;
            }
        }
        if (ok && L <= R) {
            __int128 M = (__int128)L * n + i;
            if (M <= ans) {
                int m = M;
                if (m < ans) ans = m;
            }
        }
        for (int d = 0; d < 4; d ++ )
            cur[d] += dirs[d][0] * X[i] + dirs[d][1] * Y[i] + k;
    }

    if (ans == INF) cout << -1 << "\n";
    else cout << ans << "\n";
}

signed main() {
    int T; fin >> T;

    while (T -- ) solve();
    return 0;
}