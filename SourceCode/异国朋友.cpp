/*
    @ Author:       Eric / Sky__White
    @ Filename:     异国朋友.cpp
    @ Date:         26/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/


#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>

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

using namespace std; Read fin;
const int INF = 0x3f3f3f3f3f3f3f3f;

struct Node {
    int d, v, c;
    bool operator>(const Node& o) const { return d > o.d; }
};

signed main() {
    // freopen("friend.in", "r", stdin);
    // freopen("friend.out", "w", stdout);

    int N, M, K, L; fin >> N >> M >> K >> L;

    vector<int> A(N + 1), B(L);

    for (int i = 1; i <= N; i ++ ) fin >> A[i];
    for (int i = 0; i < L; i ++ ) fin >> B[i];

    vector<vector<pair<int, int> > > g(N + 1);
    for (int i = 0; i < M; i ++ ) {
        int u, v, w; fin >> u >> v >> w;

        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    vector<vector<pair<int, int> > > G(N + 1, vector<pair<int, int> >(2));
    for (int i = 1; i <= N; i ++ ) G[i][0] = G[i][1] = {INF, 0};

    priority_queue<Node, vector<Node>, greater<Node> > pq;
    for (int b : B) pq.push({0, b, A[b]});

    while (!pq.empty()) {
        Node cur = pq.top(); pq.pop();
        int d = cur.d; int v = cur.v, c = cur.c;

        if (G[v][0].second == c || G[v][1].second == c) continue;
        if (G[v][1].second != 0) continue;

        if (G[v][0].second == 0) G[v][0] = {d, c};
        else G[v][1] = {d, c};

        for (auto& e : g[v]) {
            pq.push({d + e.second, e.first, c});
        }
    }

    for (int i = 1; i <= N; i ++ ) {
        int c1 = G[i][0].second, d1 = G[i][0].first;
        int c2 = G[i][1].second, d2 = G[i][1].first;
        int ans = 0;

        if (c1 == 0) ans = -1;
        else if (A[i] != c1) ans = d1;
        else if (c2 == 0) ans = -1;
        else ans = d2;

        cout << ans << " ";
    }
    cout << endl;
    return 0;
}