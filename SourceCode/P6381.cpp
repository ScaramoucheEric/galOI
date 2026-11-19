/*
    @ Author:       Eric / Sky__White
    @ Filename:     P6381.cpp
    @ Date:         27/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <utility>

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

struct Node { 
    int v, w, l;
};

const int MAXV = 100000;
int spf[MAXV + 1];

void pre_solve() {
    for (int i = 2; i <= MAXV; i ++ )
        if (spf[i] == 0)
            for (int j = i; j <= MAXV; j += i)
                if (spf[j] == 0)
                    spf[j] = i;
}

pair<int, int> get(int w, int k) {
    int sig = 1, csig = 1;
    bool inf = false;
    int x = w;

    while (x > 1) {
        int p = spf[x], cnt = 0;
    
        while (x % p == 0) x /= p, cnt ++ ;
        int r = cnt % k;
    
        if (r != 0) {
            for (int i = 0; i < r; i ++ ) sig *= p;
            if (!inf) {
                int pw = k - r;
                for (int i = 0; i < pw; i ++ ) {
                    if (csig > MAXV / p) { inf = true; break; }
                    csig *= p;
                }
            }
        }
    }
    
    if (inf) csig = MAXV + 1;
    
    return make_pair(sig, csig);
}

void solve() {
    int n, m, k; fin >> n >> m >> k;

    vector<vector<Node> > g(n + 1);
    vector<int> indeg(n + 1);

    for (int i = 0; i < m; i ++ ) {
        int u, v, w, l; fin >> u >> v >> w >> l;

        g[u].push_back({v, w, l});
        indeg[v] ++ ;
    }

    queue<int> q;
    for (int i = 1; i <= n; i ++ )
        if (indeg[i] == 0)
            q.push(i);

    vector<int> order;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);

        for (Node e : g[u]) {
            indeg[e.v] -- ;
            if (indeg[e.v] == 0)
                q.push(e.v);
        }
    }

    vector<map<int, int>> nm(n + 1);
    int ans = 0;

    for (int u : order) {
        for (Node e : g[u]) {
            pair<int, int> sc = get(e.w, k);

            int sig = sc.first, csig = sc.second;
            int dp = e.l;
            
            auto it = nm[u].find(sig);

            if (it != nm[u].end()) dp += it->second;
            
            if (dp > ans) ans = dp;
            
            if (csig <= MAXV) {
                int &t = nm[e.v][csig];
                if (dp > t) t = dp;
            }
        }
    }

    cout << ans << "\n";
}

signed main() {
    pre_solve();
    solve();
    return 0;
}