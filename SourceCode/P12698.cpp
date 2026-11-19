#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <cstdio>
#include <queue>

namespace std {
    class Read {
        public:
        template<typename T>
        inline Read operator >> (T & u) {
            T sum = 0; short opt = 1;
            char ch = getchar();
            while(!isdigit(ch)) opt = (ch == '-') ? -1 : 1, ch = getchar();
            while( isdigit(ch)) sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
            u = sum * opt; return *this;
        }
    };
}
#define int long long
#define all(a) a.begin(), a.end()
#define endl "\n"
#define IO(u) freopen(u ".in", "r", stdin), freopen(u ".out", "w", stdout);

using namespace std; Read fin;

#undef int

signed main() {
    int n; fin >> n;

    vector<vector<int> > G(n + 1);
    vector<int> fa_tree(n + 1, 0);
    vector<int> fa(n + 1), sz(n + 1);
    vector<bool> vis(n + 1), used(n + 1);

    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        fin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    queue<int> que;
    que.push(1);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int v : G[u]) {
            if (v == fa_tree[u]) continue;
            fa_tree[v] = u;
            que.push(v);
        }
    }

    function<int(int)> find = [&](int x) -> int {
        if (fa[x] == x) return x;
        return fa[x] = find(fa[x]);
    };

    function<void(int, int)> merge = [&](int x, int y) -> void {
        int rx = find(x), ry = find(y);
        if (rx == ry) return;
        if (sz[rx] > sz[ry]) {
            fa[ry] = rx;
            sz[rx] += sz[ry];
        } else {
            fa[rx] = ry;
            sz[ry] += sz[rx];
        }
    };

    int q;
    fin >> q;
    while (q--) {
        int k; fin >> k;

        vector<int> opt(k);

        for (auto &x : opt) {
            fin >> x;
            fa[x] = x;
            sz[x] = 1;
            vis[x] = true;
        }

        for (auto u : opt) {
            int p = fa_tree[u];
            if (p && vis[p]) merge(u, p);
        }

        long long ans = 0;

        vector<int> tt;

        for (auto u : opt) {
            int rx = find(u);

            if (used[rx]) continue;

            ans += 1LL * sz[rx] * (sz[rx] - 1) / 2;
            
            used[rx] = 1;
            tt.push_back(rx);
        }

        cout << ans << endl;

        for (auto x : opt) vis[x] = false;

        for (auto r : tt) used[r] = 0;
    }
    return 0;
}