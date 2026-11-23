/*
    @ Author:       Eric / Sky__White
    @ Filename:     [AcWing367].cpp
    @ Time:         11/26/2025
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
    int n; fin >> n;
    vector<vector<int> > G(n + 1);

    for (int i = 1; i <= n; i ++ ) {
        int x;
        do {
            fin >> x;
            if (x) G[i].push_back(x);
        } while(x);
    }

    vector<int> dfn(n + 1), low(n + 1); int stp = 0;
    vector<int> id(n + 1); int cnt = 0;

    stack<int> stk; vector<bool> in_stk(n + 1);

    function<void(int)> tarjan = [&](int u) {
        dfn[u] = low[u] = ++ stp ;
        stk.push(u), in_stk[u] = true;

        for (auto v : G[u]) {
            if (!dfn[v]) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            } else if (in_stk[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }

        if (dfn[u] == low[u]) {
            int y;
            do {
                y = stk.top(); stk.pop();
                in_stk[y] = false;
                id[y] = cnt;
                // cout << y << " ";
            } while(y != u);
            // cout << endl;
            cnt ++ ;
        }
    };

    for (int i = 1; i <= n; i ++ )
        if (!dfn[i])
            tarjan(i);

    vector<int> ind(cnt), out(cnt);

    for (int i = 1; i <= n; i ++ ) {
        for (auto j : G[i]) {
            if (id[i] == id[j]) continue;
            out[id[i]] ++ ;
            ind[id[j]] ++ ;
        }
    }

    // cout << cnt << endl;
    // for (int i = 1; i <= n; i ++ )
    //     cout << id[i] << " ";
    // cout << endl << endl;

    int cnt_in = 0, cnt_out = 0;
    for (int i = 0; i < cnt; i ++ )
        cnt_in += (ind[i] == 0),
        cnt_out += (out[i] == 0);

    // for (int i = 0; i < cnt;  i ++ )
    //     cout << i << " " << ind[i] << " " << out[i] << endl;

    cout << cnt_in << endl;

    if (cnt == 1) cout << 0 << endl;
    else cout << max(cnt_in, cnt_out) << endl;
}