/*
    @ Author:       Eric / Sky__White
    @ Filename:     P11519.cpp
    @ Date:         04/08/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/


#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <queue>
#include <ctime>
#include <cstdio>
#include <unordered_set>

namespace std {
    class Read {
        public:
        template<typename T>
        inline Read operator >> (T & x) {
            T sum = 0; signed opt = 1;
            char ch = getchar();
            while(!isdigit(ch)) opt = (ch == '-') ? -1 : 1, ch = getchar();
            while( isdigit(ch)) sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
            x = sum * opt; return (*this);
        }
    };
}
#define int long long
#define all(a) a.begin(), a.end()
#define IO(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout);

using namespace std; Read fin;

const int INF = 0x3f3f3f3f3f3f3f3f;

int n, m, E;
int ans, cur, t;
vector<int> del, tim, siz, col;

vector<int> wst; 

struct Hash {
    inline int operator ()(int x) const {
        x ^= x << 13;
        x ^= x >> 11;
        x ^= x << 7;
        return x;
    }
};

vector<unordered_set<int, Hash> > tr;

inline void add_edge(int x, int y) {
    tr[x].insert(y);
    tr[y].insert(x);
}

inline void del_edge(int x, int y) {
    tr[x].erase(y);
    tr[y].erase(x);
}

void bfs(int x, int rt) {
    tim[x] = t;
    siz[rt] ++ ;
    col[x] = rt;
    for (int to : tr[x]) {
        if (tim[to] == t) continue;
        bfs(to, rt);
    }
}

inline int link(int x, int y) {
    add_edge(x, y);
    if (siz[col[x]] < siz[col[y]]) swap(x, y);
    
    int res = 1ll * siz[col[x]] * siz[col[y]];
    siz[col[y]] = 0;
    wst.push_back(col[y]);
    
    tim[x] = t;
    bfs(y, col[x]);
    return res;
}

struct Node {
    int u;
    unordered_set<int, Hash>::iterator it;
};

inline int cut(int x, int y) {
    del_edge(x, y);
    queue<Node> p, q;

    if (!tr[x].empty()) p.push({x, tr[x].begin()});
    if (!tr[y].empty()) q.push({y, tr[y].begin()});

    auto work = [&](queue<Node>& Q) {
        auto [u, it] = Q.front();
        tim[u] = -t; 
        Q.pop();

        int v = *it;
        if (tr[v].size() > 1) {
            auto to = tr[v].begin();
            if (*to == u) to ++ ; 
            Q.push({v, to});
        }

        it ++ ;
        if (it != tr[u].end() && tim[*it] == -t) {
            it ++ ; 
        }
        if (it != tr[u].end()) {
            Q.push({u, it});
        }
    };

    while (!p.empty() && !q.empty()) {
        work(p);
        work(q);
    }

    if (p.empty()) swap(x, y); 

    int rt = wst.back();
    wst.pop_back();
    
    
    bfs(y, rt);
    siz[col[x]] -= siz[col[y]];
    
    return 1ll * siz[col[x]] * siz[col[y]];
}

inline void solve() {
    fin >> E; fin >> n >> m;
    del.resize(m + 1), tim.resize(n + 1);
    siz.resize(n + 1), col.resize(n + 1);

    tr.resize(n + 1 << 2);
    
    for (int i = 1; i <= n; i ++ ) {
        col[i] = i;
        siz[i] = 1;
    }

    for (t = 1; t <= m; t ++ ) {
        del[t] = del[t - 1];
        int opt;
        fin >> opt;
        
        if (opt != 3) {
            int x, y;
            fin >> x >> y;
            if (E) {
                x ^= ans;
                y ^= ans;
            }
            if (opt == 1) {
                cur += link(x, y);
            } else {
                del[t] += cut(x, y);
            }
        } else {
            int x;
            fin >> x;
            if (E) {
                x ^= ans;
            }
            ans = cur - del[t - x];
            
            cout << ans << "\n";
        }
    }
}

signed main() {
    #ifndef ONLINE_JUDGE
    IO("a");
    #endif

    // int T; fin >> T;

    // while(T -- ) {
        solve();
    // }

    return 0;
}