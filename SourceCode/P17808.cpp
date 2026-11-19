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
#define endl "\n"
#define IO(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout);

using namespace std; Read fin;

const int INF = 0x3f3f3f3f3f3f3f3f;

void solve();

signed main() {
    #ifndef ONLINE_JUDGE
    IO("P17808")
    #endif

    int T = 1; fin >> T;

    while(T -- ) {
        solve();
    }
}

void solve() {
    int n, m, k; fin >> n >> m >> k;

    struct Edge {
        int u, v, w, c;
        
        bool operator < (const Edge W) const {
            if (c != W.c) return c < W.c;
            if (w != W.w) return w > W.w;
            if (u != W.u) return u < W.u;
            return v < W.v;
        }
    }; vector<Edge> e;

    vector<int> fa(n + 1);

    for (int i = 1; i <= n; i ++ )
        fa[i] = i;

    function<int(int)> find = [&](int x) -> int {
        if (fa[x] == x) return x;
        return fa[x] = find(fa[x]);
    };

    int cnt = 0, sum = 0;

    for (int i = 1; i <= m; i ++ ) {
        int u, v, w, c; fin >> u >> v >> w >> c;
        if (c)
            e.push_back({u, v, w, c});
        else {
            sum += w;
            if (find(u) != find(v))
                fa[find(u)] = find(v);
        }
    }

    sort(all(e));

    vector<bool> st(e.size(), false);
    for (int i = 0; i < e.size(); i ++ ) {
        int u = e[i].u, v = e[i].v, w = e[i].w, c = e[i].c;

        if (find(u) == find(v)) continue;

        cnt += c;
        st[i] = true;
        sum += w;

        fa[find(u)] = find(v);
    }

    int opt = 0;

    for (int i = 1; i <= n; i ++ )
        if (find(i) == i) opt ++ ;

    if (opt != 1) {
        cout << -1 << endl;
        return ;
    }

    if (cnt == k) {
        cout << sum << endl;
    } else if (cnt > k) {
        cout << -1 << endl;
    } else {
        for (int i = 0; i < e.size(); i ++ ) {
            if (st[i]) continue;
            st[i] = true;
            cnt ++ ;
            sum += e[i].w;
            if (cnt == k) break;
        }

        cout << sum << endl;
    }
}