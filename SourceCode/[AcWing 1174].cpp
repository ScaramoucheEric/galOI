/*
    @ Author:       Eric / Sky__White
    @ Filename:     [AcWing1174].cpp
    @ Time:         11/25/2025
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <functional>
#include <stack>

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
#define int long long
#define all(a) a.begin(), a.end()

using namespace std;

const int INF = 0x3f3f3f3f3f3f3f3f;

signed main() {
    int n, m; fin >> n >> m;

    vector<vector<int> > G(n + 1);

    for (int i = 1; i <= m; i ++ ) {
        int a, b; fin >> a >> b;
        G[a].push_back(b);
    }

    vector<int> dfn(n + 1), low(n + 1); int stp = 0;

    stack<int> stk; vector<bool> in_stk(n + 1, false);
    vector<vector<int> > scc;
    vector<int> id(n + 1);

    function<void(int)> tarjan = [&](int u) {
        dfn[u] = low[u] = ++ stp ;
        stk.push(u);
        in_stk[u] = true;

        for (auto v : G[u]) {
            if (!dfn[v]) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            } else if(in_stk[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }

        if (low[u] == dfn[u]) {
            scc.push_back({u}); 
            in_stk[u] = false;
            id[u] = scc.size() - 1;
            int y;
            while(stk.size() and in_stk[stk.top()]) {
                y = stk.top(); stk.pop(); scc.back().push_back(y);
                id[y] = scc.size() - 1;
                in_stk[y] = false;
            } 
            while(stk.size() and !in_stk[stk.top()]) stk.pop();
        }
    };

    for (int i = 1; i <= n; i ++ ) {
        if (!dfn[i])
            tarjan(i);
    }

    vector<int> outd(scc.size());

    for (int u = 1; u <= n; u ++ ) {
        for (auto v : G[u]) {
            if (id[u] != id[v])
                outd[id[u]] ++ ;
        }
    }

    int count = 0, sum = 0;

    for (int i = 0; i < scc.size(); i ++ ) {
        if (outd[i] == 0) {
            count ++ ;
            sum += scc[i].size();
        }

        if (count >= 2) return 0 & puts("0");
    }

    cout << sum << endl;

    // for (int i = 1; i <= n; i ++ ) {
    //     cout << i << " " << dfn[i] << " " << low[i] << endl;
    // }

    // cout << scc.size() << endl;

    // for (int i = 0; i < scc.size(); i ++ ) {
    //     cout << i << " " << outd[i] << ": ";
    //     for (int j : scc[i])
    //         cout << j << " ";
    //     cout << endl;
    // }
}