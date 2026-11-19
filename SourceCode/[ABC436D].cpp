/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC436D].cpp
    @ Time:         12/13/2025
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
            x = sum * opt; return *this;
        }
    };
}
#define int long long
#define all(a) a.begin(), a.end()

using namespace std; Read fin;

const int INF = 0x3f3f3f3f3f3f3f3f;

const int dx[] = {0,+1,-1, 0, 0},
          dy[] = {0, 0, 0,+1,-1};

signed main() {
    int n, m; fin >> n >> m;

    vector<string> arr(n + 1);
    unordered_map<char, vector<pair<int,int> > > st;

    for (int i = 1; i <= n; i ++ )
        cin >> arr[i], arr[i] = " " + arr[i];

    for (int i = 1; i <= n; i ++ ) {
        for (int j = 1; j <= m; j ++ ) {
            if (arr[i][j] != '#' and arr[i][j] != '.')
                st[arr[i][j]].push_back({i, j});
        }
    }

    vector<vector<int> > dist(n + 1, vector<int>(m + 1, INF));
    vector<vector<bool> > vis(n + 1, vector<bool>(m + 1, false));
    queue<pair<int,int> > q;

    q.push({1, 1}); dist[1][1] = 0;

    while(q.size()) {
        auto [x, y] = q.front(); q.pop();

        if (x == n and y == m) {
            cout << dist[x][y] << endl;
            return 0;
        }
        
        for (int i = 1; i <= 4; i ++ ) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx > n or nx < 1 or ny > m or ny < 1) continue;
            if (arr[nx][ny] == '#') continue;
            if (dist[nx][ny] != INF) continue;
            if (vis[nx][ny]) continue;

            dist[nx][ny] = dist[x][y] + 1;
            vis[nx][ny] = true;
            q.push({nx, ny});
        }

        if (arr[x][y] != '.') {
            for (auto [nx, ny] : st[arr[x][y]]) {
                if (dist[nx][ny] != INF) continue;
                if (vis[nx][ny]) continue;
                dist[nx][ny] = dist[x][y] + 1;
                vis[nx][ny] = true;
                q.push({nx, ny});
            }
            st[arr[x][y]].clear();
        }
    }

    // for (int i = 1; i <= n; i ++ ) {
    //     for (int j = 1; j <= m; j ++ )
    //         cout << dist[i][j] << " ";
    //     cout << endl;
    // }
    if (dist[n][m] == INF)
        puts("-1");
    else
        cout << dist[n][m] << endl;

    return 0;
}