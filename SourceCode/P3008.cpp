/*
    @ Author:       Eric / Sky__White
    @ Filename:     P3008.cpp
    @ Date:         30/06/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <functional>
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

using PII = pair<int, int>;

const int INF = 0x3f3f3f3f3f3f3f3f;

signed main() {
    int n, r, p, s; fin >> n >> r >> p >> s;

    vector<vector<PII> > G(n + 1);
    vector<int> dis(n + 1, INF);
    vector<bool> vis(n + 1, false);

    for (int i = 1; i <= r; i ++ ) {
        int u, v, w;
        fin >> u >> v >> w;
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }

    for (int i = 1; i <= p; i ++ ) {
        int u, v, w; fin >> u >> v >> w;
        G[u].push_back({v, w});
    }

    deque<int> q;
    dis[s] = 0;
    q.push_back(s);
    vis[s] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        vis[u] = false;

        for (auto &e : G[u]) {
            int v = e.first, w = e.second;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                if (!vis[v]) {
                    if (!q.empty() && dis[v] >= dis[q.front()]) q.push_back(v);
                    else q.push_front(v);
                    vis[v] = true;
                }
            }
        }
    }

    for (int i = 1; i <= n; i ++ ) {
        if (dis[i] == INF) puts("NO PATH");
        else cout << dis[i] << endl;
    }

    return 0;
}