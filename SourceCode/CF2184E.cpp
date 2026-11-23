/*
    @ Author:       Eric / Sky__White
    @ Filename:     CF2184E.cpp
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

#define int long long

struct Node {
    int x, id;
    bool operator <(const Node &t) const {
        return (x == t.x ? id < t.id : x < t.x);
    }
};

void solve() {
    int n; fin >> n; vector<int> a(n + 1), ans(n + 1), c(n + 1);

    for (int i = 1; i <= n; i ++ ) {
        fin >> a[i];
        ans[i] = 0;
    }
    
    vector<Node> d(n);

    for (int i = 1; i < n; i ++ )
        c[i] = abs(a[i + 1] - a[i]), d[i] = {c[i], i};

    sort(1 + all(d));

    set<int> s;
    s.insert(0), s.insert(n);

    for (int i = 1; i < n; i ++ ) {
        int up = *s.lower_bound(d[i].id);
        int dn = *prev(s.lower_bound(d[i].id));
        ans[d[i].x] += (up - d[i].id) * (d[i].id - dn);
        s.insert(d[i].id);
    }

    for (int i = n - 1; i >= 1; i -- )
        ans[i] += ans[i + 1];

    for (int i = 1; i < n; i ++ )
        cout << ans[i] << " ";
    cout << "\n";
}

signed main() {
    int T; fin >> T;

    while(T -- ) {
        solve();
    }
}