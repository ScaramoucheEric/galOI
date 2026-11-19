/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC481E].cpp
    @ Date:         24/10/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <cstdio>
#include <vector>
#include <deque>

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
#define IO(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout)
#define endl "\n"

using namespace std; Read fin;

const int INF = 0x3f3f3f3f3f3f3f3f;
using PII = pair<int, int> ;

#define  cross(a, b) (a.x * b.y - a.y * b.x)

struct Point {
    int x, y;
    bool operator < (const Point& b) const {
        bool ua = (y > 0 || (y == 0 && x > 0));
        bool ub = (b.y > 0 || (b.y == 0 && b.x > 0));
        
        if (ua != ub) return ua > ub;
        Point a = {x, y};
        
        return cross(a, b) > 0;
    }
};


void solve() {
    int n; fin >> n;

    vector<Point> p(n);

    for (int i = 0; i < n; ++i) {
        fin >> p[i].x >> p[i].y;
    }

    if (n == 1) {
        cout << 1 << "\n";
        return;
    }

    sort(all(p));

    int ans = 0;
    int j = 0; 

    for (int i = 0; i < n; ++i) {
        if (j < i + 1) j = i + 1;
        
        while (j < i + n && cross(p[i], p[j % n]) > 0) {
            j++;
        }
        
        ans = max(ans, j - i);
    }

    cout << ans << "\n";
}

signed main() {
    int T; fin >> T;

    while (T--) {
        solve();
    }
    return 0;
}