/*
    @ Author:       Eric / Sky__White
    @ Filename:     P2680.cpp
    @ Date:         06/11/2026
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

using PII = pair<int, int>;

signed main() {
    int n, m; fin >> n >> m;

    vector<vector<PII> > G(n + 1);

    for (int i = 1; i < n; i ++ ) {
        int a, b, c; fin >> a >> b >> c;
        G[a].push_back({b, c});
        G[b].push_back({a, c});
    }

    vector<vector<int> > st(20, vector<int>(n + 1));
    vector<int> dep(n + 1);

    function<void(int,int)> dfs = [&](int u, int fa) -> void {
        st[0][u] = fa;
        dep[u] = dep[fa] + 1;

        for (int i = 1; i < 20; i ++ )
            st[i][u] = st[i - 1][st[i - 1][u]];

        for (auto [v, w] : G[u]) {
            if (v == fa) continue;
            dfs(v, u);
        }
    };

    dfs(1, 0);

    function<int(int, int)> find = [&](int a, int b) -> int {
        if (dep[a] < dep[b]) swap(a, b);
        
        int x = dep[a] - dep[b];

        int opt = 0;
        while(x) {
            if (x & 1) a = st[opt][a];
            opt += 1;
            x >>= 1;
        }
        
        for (int i = 19; ~i; i -- ) {
            if (st[i][a] != st[i][b])
                a = st[i][a], b = st[i][b];
        }
        
        if (a == b) return a;

        return st[0][a];
    };

    vector<int> c(n + 1);

    while(m -- ) {
        int u, v; fin >> u >> v;
        c[u] += 1;
        c[v] += 1;
        int opt = find(u, v);
        c[opt] -= 1;
        c[st[0][opt]] -= 1;
    }

    int res = 0;

    dfs = [&](int u, int fa) {
        for (auto [v, w] : G[u]) {
            if (v == fa) continue;
            dfs(v, u);
            c[u] += c[v];
        }
    };

    int ans = 0;

    dfs(1, 0);

    for (int i = 1; i <= n; i ++ ) {
        for (auto [j, w] : G[i])
            res += min(c[i], c[j]) * w,
            ans = max(ans, min(c[i], c[j]) * w);
    }

    for (int i = 1; i <= n; i ++ )
        cout << i << " " << c[i] << endl;

    cout << res - ans << endl;
    cout << res << " " << ans << endl;
}