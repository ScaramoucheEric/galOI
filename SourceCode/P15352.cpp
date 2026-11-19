/*
    @ Author:       Eric / Sky__White
    @ Filename:     P15352.cpp
    @ Date:         05/08/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <ctime>
#include <functional>
#include <queue>
#include <map>

namespace std {
    class Read {
        public:
        template<typename T>
        inline Read operator >> (T & x) {
            T sum = 0; short opt = 1;
            char ch = getchar();
            while(!isdigit(ch)) opt = (ch == '-') ? -1 : 1, ch = getchar();
            while( isdigit(ch)) sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
            x = sum * opt; return (*this);
        }
    };
}
#define int long long
#define all(a) a.begin(), a.end()
#define IO(x) freopen(x ".in", "r",stdin), freopen(x ".out", "w", stdout)

using namespace std; Read fin;

#undef int

signed main() {
    #ifndef ONLINE_JUDGE
    IO("a");
    #endif
    int n, q; fin >> n >> q;

    vector<vector<int> > G(n + 1);
    vector<int> L(n + 1), R(n + 1);
    vector<int> fa(n + 1); for (int i = 1; i <= n; i ++ ) fa[i] = i;

    function<int(int)> find = [&](int x) -> int {
        if (fa[x] == x) return x;
        return fa[x] = find(fa[x]);
    };
    function<void(int, int)> merge = [&](int a, int b) -> void {
        if (find(a) == find(b)) return ;
        L[find(b)] = min(L[find(b)], L[find(a)]);
        R[find(b)] = max(R[find(b)], R[find(a)]);
        fa[find(a)] = find(b);
    };

    

    for (int i = 1; i <= n; i ++ )
        L[i] = R[i] = i;

    while(q -- ) {
        int op; fin >> op;

        if (op - 1) {
            int l, r, len; fin >> l >> r >> len;
            for (int i = 0; i < len; i ++ ) {
                merge(i + l, i + r);
            }
        } else {
            int x; fin >> x;
            cout << L[find(x)] << " " << R[find(x)] << "\n";
        }
    }

    // cout << clock() * 1.0 / CLOCKS_PER_SEC << endl;

    return 0;
}