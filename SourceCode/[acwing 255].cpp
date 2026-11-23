/*
    @ Author:       Eric / Sky__White
    @ Filename:     [acwing 255].cpp
    @ Date:         25/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <functional>

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

class SegTree {
    public:
    struct Node {
        int l, r, minn, maxx, s;
    }; vector<Node> t;
    vector<int> root; int n;
    const Node Null = {0, 0, INF, 0, 0};

    SegTree(int N) : n(N) {
        root.push_back(0);
        t.resize(2, Null);
    }

    int clone(int pre) {
        t.push_back(t[pre]);
        return t.size();
    }
    int insert(int pre, int l, int r, int x, int k) {
        int p = clone(pre);

        if (l == r) {
            if (x == l)
                t[p].minn = t[p].maxx = k, t[p].s ++ ;
            return p;
        }

        int mid = l + r >> 1;

        if (l <= mid) t[p].l = insert(t[p].l, l, mid, x, k);
        if (r <  mid) t[p].r = insert(t[p].r, mid + 1, r, x, k);

        t[p].minn = min(t[t[p].l].minn, t[t[p].r].minn);
        t[p].maxx = max(t[t[p].l].maxx, t[t[p].r].maxx);
        t[p].s ++ ;

        return p;
    }

    int query(int p, int l, int r, int L, int R, int x) {
        if (!p) return INF;
        if (l >= L and r <= R) {
            
        }
    }
};

signed main() {
    int n, m; fin >> n >> m;

    vector<int> arr(n + 1);

    for (int i = 1; i <= n; i ++ ) {
    }
}