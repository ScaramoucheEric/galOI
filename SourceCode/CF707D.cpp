/*
    @ Author:       Eric / Sky__White
    @ Filename:     CF707D.cpp
    @ Date:         17/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/


#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <stack>
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

class SegTree {
    public:
    struct Node {
        int l, r, res, lazy;
    }; vector<Node> t;
    vector<int> root;

    void build(int &p, int l, int r) {
        t.push_back({0, 0, 0, 0});
        p = t.size() - 1;
        if (l == r) {
            return ;
        }

        int mid = l + r >> 1;

        int n_l, n_r;
        build(n_l, l, mid), build(n_r, mid + 1, r);
        t[p].l = n_l, t[p].r = n_r;

        push_up(p);
    }

    int reverse(int pre, int l, int r, int L, int R) {
        t.push_back(t[pre]);
        int p = t.size() - 1;

        if (l >= L and r <= R) {
            t[p].res = r - l + 1 - t[p].res;
            t[p].lazy ^= 1;
            return p;
        }
        push_down(p, l, r);

        int mid = l + r >> 1;
        
        if (L <= mid)
            t[p].l = reverse(t[p].l, l, mid, L, R);
        if (R >  mid)
            t[p].r = reverse(t[p].r, mid + 1, r, L, R);

        push_up(p);

        return p;
    }
    void push_up(int p) {
        t[p].res = t[t[p].l].res + t[t[p].r].res;
    }

    void push_down(int p, int l, int r) {
        if (t[p].lazy == 0 or l == r) return ;

        t.push_back(t[t[p].l]);
        t[p].l = t.size() - 1;
        t.push_back(t[t[p].r]);
        t[p].r = t.size() - 1;
        
        int mid = l + r >> 1;

        t[t[p].l].lazy ^= t[p].lazy;
        t[t[p].r].lazy ^= t[p].lazy;
        t[t[p].l].res = mid - l + 1 - t[t[p].l].res;
        t[t[p].r].res = r - mid - t[t[p].r].res;

        t[p].lazy = 0;

        return ;
    }

    int query(int p, int l, int r, int L, int R) {
        if (L <= l && r <= R) return t[p].res;
        push_down(p, l, r);

        int mid = l + r >> 1, res = 0;

        if (L <= mid) res += query(t[p].l, l, mid, L, R);
        if (R > mid)  res += query(t[p].r, mid + 1, r, L, R);
        return res;
    }
};

signed main() {
    int n, m, q; fin >> n >> m >> q;

    SegTree t; t.root.push_back(-1);

    t.build(t.root[0], 1, n * m);

    for (int opt = 1; opt <= q; opt ++ ) {
        int op; fin >> op;

        if (op == 1) {
            int i, j; fin >> i >> j;
            int rt = -1;
            if (t.query(t.root[opt - 1], 1, n * m, (i - 1) * m + j, (i - 1) * m + j) == 0)
                rt = t.reverse(t.root[opt - 1], 1, n * m, (i - 1) * m + j, (i - 1) * m + j);
            if (rt != -1)
                t.root.push_back(rt);
            else t.root.push_back(t.root.back());
        } else if (op == 2) {
            int i, j; fin >> i >> j;
            int rt = -1;
            if (t.query(t.root[opt - 1], 1, n * m, (i - 1) * m + j, (i - 1) * m + j))
                rt = t.reverse(t.root[opt - 1], 1, n * m, (i - 1) * m + j, (i - 1) * m + j);
            if (rt != -1)
                t.root.push_back(rt);
            else t.root.push_back(t.root.back());
        } else if (op == 3) {
            int i; fin >> i;
            int rt = t.reverse(t.root[opt - 1], 1, n * m, (i - 1) * m + 1, i * m);
            t.root.push_back(rt);
        } else {
            int k; fin >> k;
            t.root.push_back(t.root[k]);
        }
        cout << t.query(t.root[opt], 1, n * m, 1, n * m) << endl;
    }
}