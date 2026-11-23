/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC416E].cpp
    @ Date:         24/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <functional>
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

#define int long long

const int INF = 0x3f3f3f3f3f3f3f3f;

signed main() {
    int n, m; fin >> n >> m;

    vector<vector<int> > dist(n + 1, vector<int>(n + 1, INF));

    for (int i = 1; i <= m; i ++ ) {
        int a, b, c; fin >> a >> b >> c;
        dist[a][b] = min(dist[a][b], c);
        dist[b][a] = min(dist[b][a], c);
    }

    int K, T; fin >> K >> T;

    for (int i = 1; i <= K; i ++ ) {
        int t; fin >> t;
        dist[0][t] = min(dist[0][t], T);
        dist[t][0] = 0;
    }

    for (int i = 0; i <= n; i ++ )
        dist[i][i] = 0;

    function<void(int)> Floyd = [&](int k) {
        for (int i = 0; i <= n; i ++ )
            for (int j = 0; j <= n; j ++ )
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    };

    for (int i = 0; i <= n; i ++ ) {
        Floyd(i);
    }

    int Q; fin >> Q;

    while(Q -- ) {
        int op; fin >> op;

        if (op == 1) {
            int a, b, c; fin >> a >> b >> c;
            dist[a][b] = min(dist[a][b], c);
            dist[b][a] = min(dist[b][a], c);

            Floyd(a);
            Floyd(b);
        } else if (op == 2) {
            int t; fin >> t;
            dist[0][t] = min(dist[0][t], T);
            dist[t][0] = 0;
            Floyd(t);
            Floyd(0);
        } else {
            int res = 0;
            for (int i = 1; i <= n; i ++ )
                for (int j = 1; j <= n; j ++ )
                    if (dist[i][j] < INF / 2) res += dist[i][j];
            cout << res << endl;
        }
    }
}