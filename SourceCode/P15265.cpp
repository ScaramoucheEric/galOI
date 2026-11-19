/*
    @ Author:       Eric / Sky__White
    @ Filename:     P15265.cpp
    @ Date:         28/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
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
            x = sum * opt; return (*this);
        }
    };
}
#define int long long
#define all(a) a.begin(), a.end()

using namespace std; Read fin;

const int Mod = 1e9 + 7;
const int LOG = 20;

signed main() {
    int n, q; fin >> n >> q;

    function<int(int,int)> qpow = [&](int a, int b) -> int {
        int res = 1;
        for (; b; b >>= 1, a = a * a % Mod)
            if (b & 1) res = res * a % Mod;
        return res;
    };

    vector<vector<int>> son(n + 1);
    vector<int> fa(n + 1);
    vector<int> iv(n + 1);
    for (int i = 1; i <= n; i ++ )
        iv[i] = qpow(i, Mod - 2);

    for (int i = 2; i <= n; i ++ ) {
        fin >> fa[i];
        son[fa[i]].push_back(i);
    }

    vector<int> out(n + 1), dep(n + 1), deg(n + 1);
    vector<vector<int>> up(LOG, vector<int>(n + 1));

    function<void(int)> dfs = [&](int u) -> void {
        up[0][u] = fa[u];
        for (int k = 1; k < LOG; k ++ )
            up[k][u] = up[k - 1][up[k - 1][u]];
        dep[u] = dep[fa[u]] + 1;

        for (auto &v : son[u]) {
            deg[u] ++ ;
            dfs(v);
        }

        if (u == 1) return;
        if (!deg[u]) {
            out[u] = 1;
        } else {
            int sum = 0;
            for (auto &v : son[u])
                sum = (sum + out[v]) % Mod;
            out[u] = (sum * iv[deg[u]] % Mod + 1) % Mod;
            out[u] = out[u] * dep[u] % Mod;
            out[u] = out[u] * iv[dep[u] - 1] % Mod;
        }
    };
    dfs(1);

    vector<int> g(n + 1), E(n + 1), down(n + 1);
    vector<int> s(n + 1), sE(n + 1);

    dfs = [&](int u) -> void {
        int f = fa[u];
        g[u] = (g[f] + out[u] * iv[dep[u]] % Mod) % Mod;

        int sumSf = (s[f] - out[u] + Mod) % Mod;
        int term1 = sumSf * iv[deg[f]] % Mod;
        int term2 = 1;

        int Cf = (E[f] - iv[dep[f]] * sE[f] % Mod + Mod) % Mod;
        int term3 = (deg[f] - 1) * iv[deg[f]] % Mod * Cf % Mod;

        down[u] = (term1 + term2 + term3) % Mod;
        down[u] = down[u] * deg[f] % Mod;

        E[u] = (E[f] + down[u]) % Mod;
        sE[u] = (sE[f] + E[u]) % Mod;

        int sumSon = 0;
        for (auto &v : son[u])
            sumSon = (sumSon + out[v]) % Mod;
        s[u] = sumSon;

        for (auto &v : son[u])
            dfs(v);
    };
    dfs(1);

    function<int(int, int)> lca = [&](int x, int y) -> int {
        if (dep[x] < dep[y]) swap(x, y);
        int d = dep[x] - dep[y];

        for (int k = 0; k < LOG; k ++ )
            if (d >> k & 1) x = up[k][x];

        if (x == y) return x;

        for (int k = LOG - 1; k >= 0; k -- )
            if (up[k][x] != up[k][y]) x = up[k][x], y = up[k][y];

        return up[0][x];
    };

    while (q -- ) {
        int x, y; fin >> x >> y;
        int l = lca(x, y); int ans;

        if (x == y) {
            ans = 0;
        } else if (x == l) {
            ans = (E[y] - E[x]) % Mod;
        } else {
            int part1 = (out[x] + g[fa[x]] - g[l]) % Mod;
            int Ml = sE[l] * iv[dep[l]] % Mod;
            int part3 = (E[y] - Ml) % Mod;
            ans = (part1 + part3) % Mod;
        }
        
        ans = (ans % Mod + Mod) % Mod;
        
        printf("%lld\n", ans);
    }

    return 0;
}