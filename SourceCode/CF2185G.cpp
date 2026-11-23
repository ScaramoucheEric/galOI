/*
    @ Author:       Eric / Sky__White
    @ Filename:     CF2185G.cpp
    @ Date:         13/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <unordered_map>
#include <unordered_set>
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
            x = sum * opt;
            return *this;
        }
    };
}
#define int long long
#define all(a) a.begin(), a.end()

using namespace std; Read fin;

void solve() {
    int n; fin >> n;
    vector<vector<int>> a(n + 1);
    vector<unordered_map<int,int>> c(n + 1);
    int T = 0;
    for (int i=1; i<=n; i ++ ) {
        int l; fin >> l;
        a[i].resize(l + 1);
        a[i][0] = l;
        T += l;
        for (int j=1; j<=l; j ++ ) {
            fin >> a[i][j];
            c[i][a[i][j]] ++ ;
        }
    }
    vector<int> e(n + 1), g(n + 1);
    for (int i = 1; i <= n; i ++ ) {
        unordered_set<int> s;
        for (int j = 1; j <= a[i][0]; j ++ ) s.insert(a[i][j]);
        int cur = 0;
        while (s.count(cur)) cur ++ ;
        e[i] = cur;
        cur ++ ;
        while (s.count(cur)) cur ++ ;
        g[i] = cur;
    }
    unordered_map<int,int> tc;

    for (int i=1; i<=n; i ++ )
        for (int j=1; j<=a[i][0]; j ++ )
            tc[a[i][j]] ++ ;

    int S = 0, SM = 0;
    for (int i = 1; i <= n; i ++ ) {
        S += e[i];
        SM += a[i][0] * e[i];
    }

    int p1 = 0;
    for (int i = 1; i <= n; i ++ ) {
        for (int j = 1; j <= a[i][0]; j ++ ) {
            int x = a[i][j]; int nm;
            if (x > e[i]) nm = e[i];
            else if (x < e[i]) {
                if (c[i][x] == 1) nm = x;
                else nm = e[i];
            } else nm = e[i];
            p1 += nm;
        }
    }

    int A = p1 * (n - 1);
    int C = (n - 2) * (S * T - SM);
    int B = 0;
    for (int i = 1; i <= n; i ++ ) {
        int len = a[i][0];
        int cnt_e = 0;
        auto it = tc.find(e[i]);
        if (it != tc.end()) cnt_e = it->second;
        B += e[i] * (T - len) + cnt_e * (g[i] - e[i]);
    }

    int ans = A + B + C;
    cout << ans << '\n';
}

signed main() {
    int T; fin >> T;

    while (T -- ) solve();
    
    return 0;
}