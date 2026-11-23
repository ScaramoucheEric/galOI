/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC414F].cpp
    @ Date:         24/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <functional>
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

const int N = 200005;
const int M = 25;

int n, m;
int dis[N][M], vis[N][M];
vector<int> G[N];

struct Node {
    int u, id, val, lst;
};

queue<Node> Q;

signed main() {
    int T;
    fin >> T;

    while (T --) {
        fin >> n >> m;

        for (int i = 1; i <= n; i ++) {
            G[i].clear();
            for (int j = 0; j <= m; j ++) {
                vis[i][j] = dis[i][j] = 1e9;
            }
        }

        for (int i = 1; i < n; i ++) {
            int u, v;
            fin >> u >> v;
            G[u].push_back(v);
            G[v].push_back(u);
        }

        dis[1][0] = 0;
        Q.push({1, 0, 0, 0});

        while (!Q.empty()) {
            auto t = Q.front();
            int u = t.u, id = t.id, val = t.val, lst = t.lst;
            Q.pop();

            for (int i = 0; i < (int)G[u].size(); i ++) {
                int v = G[u][i];
                if (v == lst) continue;

                Node to = {v, (id + 1) % m, val, u};

                if (!id) to.val ++;
                if (!to.id) to.lst = 0;

                if (to.val < dis[v][to.id]) {
                    Q.push(to);
                    dis[v][to.id] = to.val;
                    vis[v][to.id] = to.lst;
                }
                else if (vis[v][to.id] && vis[v][to.id] != to.lst) {
                    Q.push(to);
                    vis[v][to.id] = 0;
                }
            }
        }

        for (int i = 2; i <= n; i ++) {
            if (dis[i][0] < 1e8) printf("%lld ", dis[i][0]);
            else printf("-1 ");
        }
        puts("");
    }

    return 0;
}