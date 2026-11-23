/*
    @ Author:       Eric / Sky__White
    @ Filename:     P3379.cpp
    @ Date:         06/02/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <random>
#include <map>
#include <queue>
#include <functional>
#include <vector>
#include <unordered_map>

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

signed main() {
    int N, M, S; fin >> N >> M >> S;

    vector<vector<int> > G(N + 1);

    for (int i = 1; i < N; i ++ ) {
        int u, v; fin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    vector<vector<int> > st(20, vector<int>(N + 1));
    vector<int> dep(N + 1, 0);

    function<void(int, int)> dfs = [&](int u, int fa) -> void {
        st[0][u] = fa;
        dep[u] = dep[fa] + 1;
        for (int i = 1; i <= 18; i ++ ) {
            st[i][u] = st[i - 1][st[i - 1][u]];
        }
        for (auto v : G[u]) {
            if (v == fa) continue;
            dfs(v, u);
        }
    };

    dfs(S, S);

    function<int(int, int)> find = [&](int a, int b) -> int {
        if (dep[a] < dep[b])
            swap(a, b);
        
        if (a == b)
            return a;

        if (dep[a] > dep[b]) {
            int t = dep[a] - dep[b];
            int opt = 0;
            while(t) {
                if (t & 1) a = st[opt][a];
                opt ++ ;
                t >>= 1;
            }
        }

        if (a == b)
            return a;

        // cout << dep[a] << " " << dep[b] << endl;

        for (int i = 18; ~i; i -- ) {
            if (st[i][a] != st[i][b])
                a = st[i][a], b = st[i][b];
        }

        return st[0][a];
    };

    while(M -- ) {
        int a, b; fin >> a >> b;
        cout << find(a, b) << endl;;
    }
}
