/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC437E].cpp
    @ Time:         12/20/2025
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <functional>
#include <map>
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
    } fin;
}
#define int long long
#define all(a) a.begin(), a.end()

using namespace std;

int idx;
map<int, set<pair<int, int> > > ne;
map<int, set<int> > num;

signed main() {
    int n; fin >> n;
    vector<int> id(n + 1), str(1);

    id.resize(n + 1);

    for (int i = 1; i <= n; i ++ ) {
        int x, y; fin >> x >> y;
        
        int u = id[x];
        int v = [&]() -> int {
            for (auto [i, _] : ne[u])
                if (i == y) return _;
            return -1;
        }();

        if (v == -1) {
            v = ++ idx;
            str.push_back(y);
            ne[u].insert({y, idx});
        }

        id[i] = v;
        num[v].insert(i);
    }

    function<void(int)> dfs = [&](int u) -> void {
        auto t = num[u];
        for (auto i : t)
            cout << i << " ";

        if (ne[u].size() == 0) return ;

        auto tt = ne[u];
        for (auto [_, v] : tt) 
            dfs(v);

        return ;
    };

    dfs(0);

    cout << endl;
}