/*
    @ Author:       Eric / Sky__White
    @ Filename:     黑夜君临.cpp
    @ Date:         15/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <unordered_map>
#include <cstdio>
#include <queue>
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

using PII = pair<int, int> ;

const int INF = 0x3f3f3f3f3f3f3f3f;

signed main() {
    // freopen("Nightreign.in", "r", stdin);
    // freopen("Nightreign.out", "w", stdout);

    int n, m, k, q; fin >> n >> m >> k >> q;

    vector<vector<PII> > G(n + 1);
    vector<int> s(k + 1);

    vector<pair<PII, int> > edge;

    for (int i = 1; i <= m; i ++ ) {
        int u, v; fin >> u >> v; int d; fin >> d;

        G[u].push_back({v, d});
        G[v].push_back({u, d});
        edge.push_back({{u, v}, d});
    }

    for (int i = 1; i <= k; i ++ ) 
        fin >> s[i], G[0].push_back({s[i], 0});

    vector<int> dis(n + 1, INF);
    function<void()> Dijkstra = [&]() -> void {
        vector<bool> st(n + 1);
        dis[0] = 0;
        priority_queue<PII, vector<PII>, greater<PII> > q;
        q.push({0, 0});

        while(q.size()) {
            auto t = q.top(); q.pop();
            int u = t.second;

            if (st[u]) continue;
            st[u] = true;

            for (auto v : G[u]) {
                if (dis[v.first] > dis[u] + v.second)
                    dis[v.first] = dis[u] + v.second,
                    q.push({dis[v.first], v.first});
            }
        }
    };

    Dijkstra();

    vector<pair<int, PII> > edges;

    for (auto i : edge) {
        int u = i.first.first, v = i.first.second, w = i.second;
        edges.push_back({dis[u] + dis[v] + w, {u, v}});
    }

    sort(all(edges));

    vector<int> fa(n + 1);
    for (int i = 1; i <= n; i ++ ) fa[i] = i;

    function<int(int)> find = [&](int x) -> int {
        if (fa[x] == x) return x;
        return fa[x] = find(fa[x]);
    };

    G.clear();
    G.resize(n + 1);

    for (auto i : edges) {
        int w = i.first, u = i.second.first, v = i.second.second;
        
        if (find(u) == find(v)) continue;

        G[u].push_back({v, w});
        G[v].push_back({u, w});

        fa[find(u)] = find(v);
    }

    vector<int> dep(n + 1);
    vector<vector<int> > dist(n + 1, vector<int>(30, INF));
    vector<vector<int> > st(n + 1, vector<int>(30));

    function<void(int, int)> dfs = [&](int u, int fa) {
        dep[u] = dep[fa] + 1;
        st[u][0] = fa;

        for (int i = 1; i <= 25; i ++ )
            st[u][i] = st[st[u][i - 1]][i - 1];

        for (int i = 1; i <= 25; i ++ )
            dist[u][i] = max(dist[u][i - 1], dist[st[u][i - 1]][i - 1]);

        for (auto v : G[u]) {
            if (v.first == fa) continue;
            dist[v.first][0] = v.second;
            dfs(v.first, u);
        }
    };

    dfs(1, 0);

    function<pair<int, int> (int, int)> lca = [&](int a, int b) -> pair<int, int> {
        if (dep[a] < dep[b]) swap(a, b);

        int opt = dep[a] - dep[b];

        int res = 0; // 找路径上最短的最大值

        int cnt = 0;
        while(opt) {
            if (opt & 1) res = max(res, dist[a][cnt]), a = st[a][cnt];
            cnt ++ ; opt >>= 1;
        }

        if (a == b) return {a, res};

        for (int i = 25; ~i; i -- ) {
            if (st[a][i] == st[b][i]) continue;
            res = max({res, dist[a][i], dist[b][i]});
            a = st[a][i], b = st[b][i];
        }

        if (a == b) return {a, res};

        return {st[a][0], max({res, dist[a][0], dist[b][0]})};
    };

    while(q -- ) {
        int a, b; fin >> a >> b;
        a = s[a], b = s[b];

        auto t = lca(a, b);

        int res = t.second;

        cout << res << endl;
    }
}