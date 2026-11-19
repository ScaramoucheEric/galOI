#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <random>
#include <ctime>

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
    } fin;
}

using namespace std;

#define int long long
#define all(a) a.begin(), a.end()

struct Node {
    int u, v, val;

    bool operator < (const Node W) const {
        return val < W.val;
    }
};
vector<int> fa;

inline int find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}

signed main() {
    // freopen("road.in", "r", stdin);
    // freopen("road.out", "w", stdout);
    
    int n, m, k; fin >> n >> m >> k;

    vector<Node> e;

    for (int i = 1; i <= m; i ++ ) {
        int u, v, w; fin >> u >> v >> w;
        e.push_back({u, v, w});
    }

    vector<vector<int> > cs_e(k + 1, vector<int>(n + 1));
    vector<int> cs_w(k + 1);
    vector<Node> WW;

    for (int i = 1; i <= k; i ++ ) {
        fin >> cs_w[i];
        for (int j = 1; j <= n; j ++ )
            fin >> cs_e[i][j], WW.push_back({j, i + n, cs_e[i][j]});
    }

    sort(all(e));

    fa.resize(n + 1 + k);

    vector<Node> rre;

    for (int i = 1; i <= n + k; i ++ )
        fa[i] = i;
    vector<int> back = fa;

    int res = 0, cnt = 0;
    vector<Node> ee;

    for (auto [u, v, w] : e) {
        if (find(u) != find(v)) {
            fa[find(u)] = find(v);
            res += w;
            cnt ++ ;

            ee.push_back({u, v, w});
        }
    }

    e = ee;

    for (int S = 0; S < 1 << k; S ++ ) {
        fa = back; 
        vector<int> cs;
        vector<Node> cs_edge;
        for (int i = 0; i < k; i ++ )
            if (S >> i & 1)
                cs.push_back(i + 1);

        int cost = 0, cnt = n + cs.size() - 1;
        
        for (int i = 0; i < cs.size(); i ++ ) {
            cost += cs_w[cs[i]];
            for (int j = 1; j <= n; j ++ )
                cs_edge.push_back({j, cs[i] + n, cs_e[cs[i]][j]});
        }
        sort(all(cs_edge));

        int pos1 = 0, pos2 = 0;

        while(pos1 < e.size() and pos2 < cs_edge.size()) {
            if (e[pos1] < cs_edge[pos2]) {
                int u, v, w;
                if (S == 0) rre.push_back(e[pos1]);
                u = e[pos1].u, v = e[pos1].v, w = e[pos1].val;

                if (find(u) != find(v)) {
                    fa[find(u)] = find(v);
                    cnt -- ;
                    cost += w;
                }

                pos1 ++ ;
            } else {
                int u, v, w;
                u = cs_edge[pos2].u, v = cs_edge[pos2].v, w = cs_edge[pos2].val;

                if (find(u) != find(v)) {
                    fa[find(u)] = find(v);
                    cnt -- ;
                    cost += w;
                }

                pos2 ++ ;
            }

            if (cnt == 0)
                break;
            if (res <= cost)
                break;
        }

        while(pos1 < e.size()) {
            if (cnt == 0)
                break;
            if (res <= cost)
                break;

            int u, v, w;
            u = e[pos1].u, v = e[pos1].v, w = e[pos1].val;
            if (S == 0) rre.push_back(e[pos1]);

            if (find(u) != find(v)) {
                fa[find(u)] = find(v);
                cnt -- ;
                cost += w;
            }

            pos1 ++ ;
        }
        while(pos2 < cs_edge.size()) {
            if (cnt == 0)
                break;
            if (res <= cost)
                break;

            int u, v, w;
            u = cs_edge[pos2].u, v = cs_edge[pos2].v, w = cs_edge[pos2].val;

            if (find(u) != find(v)) {
                fa[find(u)] = find(v);
                cnt -- ;
                cost += w;
            }

            pos2 ++ ;
        }
        // cout << cost << endl;
        res = min(res, cost);

        if (S == 0) {
            e = rre;
            // cout << pos1 << endl;
        }
    }

    cout << res << endl;

    return 0;
}