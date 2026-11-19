/*
    @ Author:       Eric / Sky__White
    @ Filename:     P10137.cpp
    @ Date:         27/08/2026
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
        inline Read & operator >> (T & x) {
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
#define IO(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout)

using namespace std; Read fin;

using PII = pair<int, int>;

constexpr int mod = 1e9 + 7;
constexpr int MAXN = 2e5;
constexpr double eps = 1e-6;
constexpr int inf = 2e9;

void solve() {
    int n, q; cin >> n >> q;
    vector<int> x(0), y(0);
    char ch;
    for(int i = 1, c; i <= n; i ++) {
        cin >> ch >> c;
        if(ch == 'V') y.push_back(c);
        else x.push_back(c);
    }

    x.push_back(inf), y.push_back(inf);
    sort(all(x)), sort(all(y));
    vector<vector<int> > bx(x.size(), vector<int> (18, 0));
    vector<vector<int> > by(y.size(), vector<int> (18, 0));
    for(int i = 0; i < 18; i ++) {
        bx[(int) x.size() - 1][i] = (int) x.size() - 1;
        by[(int) y.size() - 1][i] = (int) y.size() - 1;
    }

    for(int i = (int) x.size() - 2; i >= 0; i --) {
        bx[i][0] = ((x[i] + x[i + 1] & 1) ? i + 1 : bx[i + 1][0]);
        for(int j = 1; j < 18; j ++) {
            bx[i][j] = bx[bx[i][j - 1]][j - 1];
        }
    }
    for(int i = (int) y.size() - 2; i >= 0; i --) {
        by[i][0] = ((y[i] + y[i + 1] & 1) ? i + 1 : by[i + 1][0]);
        for(int j = 1; j < 18; j ++) {
            by[i][j] = by[by[i][j - 1]][j - 1];
        }
    }

    auto query = [&](int xi, int yi, int d) -> PII {
        int t = 0;
        int x0 = lower_bound(all(x), yi) - x.begin();
        int y0 = lower_bound(all(y), xi) - y.begin();

        if (yi < x[x0]) {
            if (d + yi <= x[x0]) return make_pair(xi, d + yi);
            d -= x[x0] - yi, t += x[x0] - yi;
        }
        if (xi < y[y0]) {
            if (d + xi <= y[y0]) return make_pair(xi + d, yi);
            d -= y[y0] - xi, t += y[y0] - xi;
        }

        for(int i = 17; ~i; i --) {
            int nx = bx[x0][i], ny = by[y0][i];
            if(x[nx] - x[x0] + y[ny] - y[y0] > d) continue;
            d -= x[nx] - x[x0] + y[ny] - y[y0], t += x[nx] - x[x0] + y[ny] - y[y0];
            x0 = nx, y0 = ny;
        }

        if(t & 1) {
            int ny = by[y0][0];
            if (y[ny] - y[y0] >= d) return make_pair(y[y0] + d, x[x0]);
            d -= y[ny] - y[y0];

            return make_pair(y[ny], x[x0] + d);
        } else {
            int nx = bx[x0][0];
            if (x[nx] - x[x0] >= d) return make_pair(y[y0], x[x0] + d);
            d -= x[nx] - x[x0];
            return make_pair(y[y0] + d, x[nx]);
        }
        
    };

    while(q --) {
        int xi, yi, d; cin >> xi >> yi >> d;
        auto [u, v] = query(xi, yi, d);
        cout << u << " " << v << "\n";
    }
}

signed main() {
    solve();

    return 0;
}
