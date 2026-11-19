/*
    @ Author:       Eric / Sky__White
    @ Filename:     P10045.cpp
    @ Date:         13/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <cstdio>
#include <array>

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

using uint = unsigned;
const uint MOD = 1u << 20;
const uint MASK = MOD - 1;

vector<array<uint, 20>> comb;

class SegTree {
    public:
        struct Node {
            array<uint, 20> s;
        };

        vector<Node> t;
        vector<uint> lazy;
        int n;

        SegTree(int n, vector<int> &a) : n(n) {
            t.resize((n << 2) + 5);
            lazy.assign((n << 2) + 5, 0);
            build(1, 1, n, a);
        }

        #define lc (p << 1)
        #define rc (p << 1 | 1)

        void build(int p, int l, int r, vector<int> &a) {
            t[p].s.fill(0);
            t[p].s[0] = 1;
            if (l == r) {
                t[p].s[1] = ((uint)(a[l] - 1)) & MASK;
                return;
            }
            int mid = (l + r) >> 1;
            build(lc, l, mid, a);
            build(rc, mid + 1, r, a);
            pushup(p);
        }

        void pushup(int p) {
            t[p].s[0] = 1;
            for (int i = 1; i < 20; ++i) {
                uint val = (t[lc].s[i] + t[rc].s[i]) & MASK;
                for (int j = 1; j < i; ++j) {
                    val = (val + (uint)(1ull * t[lc].s[j] * t[rc].s[i - j])) & MASK;
                }
                t[p].s[i] = val;
            }
        }

        void apply(int p, uint v, int len) {
            array<uint, 20> old = t[p].s;
            uint powv[20];
            powv[0] = 1;
            for (int i = 1; i < 20; ++i)
                powv[i] = (uint)(1ull * powv[i - 1] * v) & MASK;

            for (int i = 19; i >= 0; --i) {
                uint sum = 0;
                for (int j = 0; j <= i; ++j) {
                    uint c = comb[len - j][i - j];
                    uint term = (uint)(1ull * old[j] * c % MOD * powv[i - j] % MOD);
                    sum = (sum + term) & MASK;
                }
                t[p].s[i] = sum;
            }
            lazy[p] = (lazy[p] + v) & MASK;
        }

        void pushdown(int p, int l, int r) {
            if (lazy[p] == 0 || l == r) return;
            int mid = (l + r) >> 1;
            uint v = lazy[p];
            apply(lc, v, mid - l + 1);
            apply(rc, v, r - mid);
            lazy[p] = 0;
        }

        void update(int p, int l, int r, int ql, int qr, uint v) {
            if (ql <= l && r <= qr) {
                apply(p, v, r - l + 1);
                return;
            }
            pushdown(p, l, r);
            int mid = (l + r) >> 1;
            if (ql <= mid) update(lc, l, mid, ql, qr, v);
            if (qr > mid) update(rc, mid + 1, r, ql, qr, v);
            pushup(p);
        }

        array<uint, 20> query(int p, int l, int r, int ql, int qr) {
            if (ql <= l && r <= qr) return t[p].s;
            pushdown(p, l, r);
            int mid = (l + r) >> 1;
            if (qr <= mid) return query(lc, l, mid, ql, qr);
            if (ql > mid) return query(rc, mid + 1, r, ql, qr);

            array<uint, 20> left = query(lc, l, mid, ql, qr);
            array<uint, 20> right = query(rc, mid + 1, r, ql, qr);
            array<uint, 20> res;
            res.fill(0);
            res[0] = 1;
            for (int i = 1; i < 20; ++i) {
                uint val = (left[i] + right[i]) & MASK;
                for (int j = 1; j < i; ++j) {
                    val = (val + (uint)(1ull * left[j] * right[i - j])) & MASK;
                }
                res[i] = val;
            }
            return res;
        }
};

signed main() {
    int n, m;
    fin >> n >> m;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) fin >> a[i];

    comb.resize(n + 1);
    for (int i = 0; i <= n; ++i) comb[i].fill(0);
    comb[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        comb[i][0] = 1;
        for (int j = 1; j <= 19 && j <= i; ++j) {
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) & MASK;
        }
    }

    SegTree seg(n, a);

    while (m--) {
        int opt;
        fin >> opt;
        if (opt == 1) {
            int l, r, v;
            fin >> l >> r >> v;
            v %= (int)MOD;
            if (v < 0) v += MOD;
            seg.update(1, 1, n, l, r, (uint)(v));
        } else {
            int l, r;
            fin >> l >> r;
            auto res = seg.query(1, 1, n, l, r);
            uint ans = 0;
            for (int i = 0; i < 20; ++i)
                ans = (ans + res[i]) & MASK;
            printf("%u\n", ans);
        }
    }

    return 0;
}