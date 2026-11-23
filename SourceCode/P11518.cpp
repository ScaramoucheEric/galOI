/*
    @ Author:       Eric / Sky__White
    @ Filename:     P11518.cpp
    @ Date:         07/09/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdio>
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
#define IO(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout);

using namespace std; Read fin;

const int INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1000003;
const int MAXN = 500005;
const int M = (MAXN << 2);

int n, a[MAXN], lst[3][MAXN], t[3][MAXN], f[MAXN];

struct Seg {
    int l, r, v;
};

class SegTree {
    public:
    struct Node {
        int mx, sum, lazy;
    };
    Node tree[M];
    vector<Seg> pat[MAXN];

    void init() {
        for (int i = 0; i < (n << 2); i ++ ) tree[i] = {0, 0, 0};
        for (int i = 0; i <= n; i ++ ) pat[i].clear();
    }

    void push_up(int p) {
        int ls = p << 1, rs = p << 1 | 1;
        if (tree[ls].mx == tree[rs].mx) {
            tree[p].mx = tree[ls].mx;
            tree[p].sum = (tree[ls].sum + tree[rs].sum) % MOD;
        } else if (tree[ls].mx > tree[rs].mx) {
            tree[p].mx = tree[ls].mx;
            tree[p].sum = tree[ls].sum;
        } else {
            tree[p].mx = tree[rs].mx;
            tree[p].sum = tree[rs].sum;
        }
    }

    void make_tag(int p, int v) {
        tree[p].lazy += v;
        tree[p].mx += v;
    }

    void push_down(int p) {
        if (!tree[p].lazy) return;
        int ls = p << 1, rs = p << 1 | 1;
        make_tag(ls, tree[p].lazy);
        make_tag(rs, tree[p].lazy);
        tree[p].lazy = 0;
    }

    void add(int p, int l, int r, int L, int R, int v) {
        if (L > R) return;
        if (l >= L and r <= R) {
            make_tag(p, v);
            return;
        }
        push_down(p);
        int mid = l + r >> 1;
        if (L <= mid) add(p << 1, l, mid, L, R, v);
        if (R >  mid) add(p << 1 | 1, mid + 1, r, L, R, v);
        push_up(p);
    }

    void upd(int p, int l, int r, int x, int v) {
        if (l == r) {
            tree[p].sum = v;
            return;
        }
        push_down(p);
        int mid = l + r >> 1;
        if (x <= mid) upd(p << 1, l, mid, x, v);
        else upd(p << 1 | 1, mid + 1, r, x, v);
        push_up(p);
    }

    int calc(int c) {
        if (tree[1].mx == c) return tree[1].sum;
        return 0;
    }

    void modify(int id, int x, int y, int v) {
        pat[id].push_back({x, y, v});
        if (x <= y) add(1, 1, n, x, y, v);
    }


    void remove(int x) {
        for (auto &w : pat[x]) {
            if (w.l <= w.r) add(1, 1, n, w.l, w.r, -w.v);
        }
    }
};

SegTree tr1, tr2;

signed main() {
    #ifndef ONLINE_JUDGE
        IO("a");
    #endif

    fin >> n;
    for (int i = 1; i <= n; i ++ ) fin >> a[i];

    for (int i = 1; i <= n; i ++ ) {
        lst[0][i] = t[0][a[i]];
        lst[1][i] = t[2][a[i]];
        lst[2][i] = t[1][a[i]];
        t[0][a[i]] = i;
        if (i & 1) t[1][a[i]] = i;
        else t[2][a[i]] = i;
    }

    int c1 = 0, c2 = 0;
    f[0] = 1;
    tr1.init();
    tr2.init();

    for (int i = 1; i <= n; i ++ ) {
        if (i & 1) {
            tr1.modify(i, lst[0][i] + 1, n, 1);
            c1 ++ ;
        } else {
            int p = lst[0][i];
            if (p) tr1.remove(p);
            else c1 ++ ;

            cout << c1 << endl;

            tr1.modify(i, lst[2][i] + 1, p, 1);
            tr1.modify(i, i + 1, n, 1);
        }
        f[i] = (f[i] + tr1.calc(c1)) % MOD;

        if (i & 1) {
            int p = lst[0][i];
            if (p) tr2.remove(p);
            else c2 ++ ;
            tr2.modify(i, lst[1][i] + 1, p, 1);
            tr2.modify(i, i + 1, n, 1);
        } else {
            tr2.modify(i, lst[0][i] + 1, n, 1);
            c2 ++ ;
        }
        f[i] = (f[i] + tr2.calc(c2)) % MOD;
        f[i] = (f[i] + f[i - 1]) % MOD;

        tr1.upd(1, 1, n, i, f[i - 1]);
        tr2.upd(1, 1, n, i, f[i - 1]);
    }

    cout << f[n] << endl;
    return 0;
}