#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <map>
#include <functional>
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

using PII = pair<int, int>;
const int INF = 0x3f3f3f3f3f3f3f3f;

signed main() {
    #ifndef ONLINE_JUDGE
    IO("P11860");
    #endif

    int n, m; fin >> n >> m;

    struct Edge {
        int u, v, w;

        bool operator < (const Edge e) const {
            if (u != e.u)
                return u < e.u;
            if (v != e.v)
                return v < e.v;
            return w < e.w;
        }
        bool operator == (const Edge e) const {
            return w == e.w and u == e.u and v == e.v;
        }
    }; // u < v

    map<Edge, int> st; int idx = 0;

    vector<vector<pair<int, int> > > G(m + 2), g(n + 1);
    
    while(m -- ) {
        int u, v, w; fin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
        if (u > v) swap(u, v);
        st[{u, v, w}] = ++ idx;
        // cout << u << " " << v << " " << w << " " << idx << endl;
    }
    // cout << endl;

    for (int i = 1; i <= n; i ++ ) {
        sort(all(g[i]), [&](PII a, PII b) {
            return a.second < b.second;
        });
        for (int u = 0; u + 1 < g[i].size(); u ++ ) {
            int v = u + 1;
            // cout << min(i, g[i][u].first) << " " << max(i, g[i][u].first) << " " << g[i][u].second << " " << st[{min(i, g[i][u].first), max(i, g[i][u].first), g[i][u].second}] << endl;
            // cout << min(i, g[i][v].first) << " " << max(i, g[i][v].first) << " " << g[i][v].second << " " << st[{min(i, g[i][v].first), max(i, g[i][v].first), g[i][v].second}] << endl endl;
            int uu = st[{min(i, g[i][u].first), max(i, g[i][u].first), g[i][u].second}], vv = st[{min(i, g[i][v].first), max(i, g[i][v].first), g[i][v].second}], ww = abs(g[i][u].second - g[i][v].second);
            G[uu].push_back({vv, ww});
            G[vv].push_back({uu, ww});
        }
    }

    for (auto vv : g[1]) {
        int v = st[{1, vv.first, vv.second}];
        // cout << 1 << " " << vv.first << " " << vv.second << endl;
        G[0].push_back({v, vv.second});
        G[v].push_back({0, vv.second});
        // cout << v << endl;
    }
    // cout << endl;

    for (auto vv : g[n]) {
        int v = st[{vv.first, n, vv.second}];
        // cout << 1 << " " << vv.first << " " << vv.second << endl;
        G[idx + 1].push_back({v, 0});
        G[v].push_back({idx + 1, 0});
        // cout << v << endl;
    }
    // cout << endl;

    function<void(void)> Dijkstra = [&](void) -> void {
        vector<int> dist(idx + 2, INF);
        vector<bool> st(idx + 2);

        priority_queue<PII, vector<PII>, greater<PII> > q;
        q.push({0, 0});
        dist[0] = 0;

        while(q.size()) {
            auto t = q.top(); q.pop();
            int dis = t.first, u = t.second;
            // cout << u << " " << dis << endl;

            if (st[u])
                continue;
            st[u] = true;

            for (auto e : G[u]) {
                if (dist[e.first] > dis + e.second)
                    dist[e.first] = dist[u] + e.second,
                    q.push({dist[e.first], e.first});
            }
        }

        cout << dist[idx + 1] << endl;
    };

    Dijkstra();
}