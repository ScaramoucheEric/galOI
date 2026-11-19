/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC481D].cpp
    @ Date:         24/10/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <cstdio>
#include <vector>
#include <deque>

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

#define int long long
#define all(arr) arr.begin(), arr.end()
#define IO(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout)
#define endl "\n"

using namespace std; Read fin;

const int INF = 0x3f3f3f3f3f3f3f3f;
using PII = pair<int, int> ;

signed main() {
    int n, m, S, T; fin >> n >> m >> S >> T;

    vector<vector<int> > G(n + 1);

    for (int i = 1; i <= m; i ++ ) {
        int u, v; fin >> u >> v;
        G[u].push_back(v);
    }

    for (int i = 1; i <= n; i ++ ) {
        sort(all(G[i]));
    }
    
    deque<PII> q; q.push_back({0, S});
    vector<int> dist(n + 1, INF); dist[S] = 0;

    while(q.size()) {
        auto [dis, u] = q.front(); q.pop_front();

        if (dis > dist[u]) continue;

        for (int i = 0; i < G[u].size(); i ++ ) {
            if (i == 0) {
                int v = G[u][i], w = 0;
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    q.push_front({dist[v], v});
                }
            } else {
                int v = G[u][i], w = 1;
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    q.push_back({dist[v], v});
                }
            }
        }
    }

    if (dist[T] >= INF / 2) {
        cout << -1 << endl;
    } else {
        cout << dist[T] << endl;
    }

    // for (int i = 1; i <= n; i ++ )
    //     cout << i << " " << dist[i] << endl;
}