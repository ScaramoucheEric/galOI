/*
    @ Author:       Eric / Sky__White
    @ Filename:     文文的摄影布置.cpp
    @ Date:         18/07/2026
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

const int INF = 0x3f3f3f3f3f3f3f3f;

struct SegTree {
    struct Node {
        int ans, maxA, minB, max1, max2;
    }; vector<Node> t;

    vector<int> A, B;
    int n;

    SegTree(vector<int> &a, vector<int> &b) : A(a), B(b) {
        n = (int)A.size() - 1;
        t.resize(4 * (n + 2));
        build(1, 1, n);
    }

    Node merge(Node a, Node b) {
        Node res;
        res.maxA = max(a.maxA, b.maxA);
        res.minB = min(a.minB, b.minB);
        res.max1 = max({a.max1, b.max1, a.maxA - b.minB});
        res.max2 = max({a.max2, b.max2, b.maxA - a.minB});
        res.ans = max({a.ans, b.ans, a.max1 + b.maxA, a.maxA + b.max2});
        return res;
    }

    #define lc (p << 1)
    #define rc (p << 1 | 1)

    void build(int p, int l, int r) {
        if (l == r) {
            t[p].maxA = A[l];
            t[p].minB = B[l];
            t[p].max1 = t[p].max2 = t[p].ans = -INF;
            return;
        }
        int mid = (l + r) >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
        t[p] = merge(t[lc], t[rc]);
    }

    void updateA(int p, int l, int r, int pos, int val) {
        if (l == r) {
            t[p].maxA = val;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) updateA(lc, l, mid, pos, val);
        else updateA(rc, mid + 1, r, pos, val);
        t[p] = merge(t[lc], t[rc]);
    }

    void updateB(int p, int l, int r, int pos, int val) {
        if (l == r) {
            t[p].minB = val;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) updateB(lc, l, mid, pos, val);
        else updateB(rc, mid + 1, r, pos, val);
        t[p] = merge(t[lc], t[rc]);
    }

    Node query(int p, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) {
            Node Null;
            Null.maxA = Null.max1 = Null.max2 = Null.ans = -INF;
            Null.minB = INF;

            return Null;
        }
        if (ql <= l && r <= qr) {
            return t[p];
        }
        int mid = (l + r) >> 1;
        Node L = query(lc, l, mid, ql, qr);
        Node R = query(rc, mid + 1, r, ql, qr);
        return merge(L, R);
    }
};

signed main() {
    int n, m; fin >> n >> m;
    vector<int> A(n + 1), B(n + 1);
    for (int i = 1; i <= n; i++) {
        fin >> A[i];
    }
    for (int i = 1; i <= n; i++) {
        fin >> B[i];
    }
    SegTree seg(A, B);
    while (m--) {
        int op; fin >> op;
        if (op == 1) {
            int x, y; fin >> x >> y;
            seg.updateA(1, 1, n, x, y);
        } else if (op == 2) {
            int x, y; fin >> x >> y;
            seg.updateB(1, 1, n, x, y);
        } else {
            int l, r; fin >> l >> r;
            printf("%lld\n", seg.query(1, 1, n, l, r).ans);
        }
    }
    return 0;
}