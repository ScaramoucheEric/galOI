/*
    @ Author:       Eric / Sky__White
    @ Filename:     P13514.cpp
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

struct SegTree {
    struct Node {
        int cnt, sum;
    };
    vector<Node> t;
    vector<int> val;
    int n;

    SegTree(vector<int> &v) : val(v) {
        n = (int)val.size() - 1;
        t.resize(4 * (n + 2));
    }

    void push_up(int p) {
        t[p].cnt = t[p << 1].cnt + t[p << 1 | 1].cnt;
        t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum;
    }

    void update(int p, int l, int r, int pos, int v) {
        if (l == r) {
            t[p].cnt++;
            t[p].sum += v;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) update(p << 1, l, mid, pos, v);
        else update(p << 1 | 1, mid + 1, r, pos, v);
        push_up(p);
    }

    int query(int p, int l, int r, int need) {
        if (t[p].sum < need) return -1;
        if (l == r) {
            int v = val[l];
            return (need + v - 1) / v;
        }
        int mid = (l + r) >> 1;
        if (t[p << 1 | 1].sum >= need) {
            return query(p << 1 | 1, mid + 1, r, need);
        } else {
            int res = query(p << 1, l, mid, need - t[p << 1 | 1].sum);
            if (res == -1) return -1;
            return res + t[p << 1 | 1].cnt;
        }
    }
};

struct Query {
    int x, p, id;
    bool operator<(const Query &other) const {
        return x < other.x;
    }
};

signed main() {
    int n, q; fin >> n >> q;
    vector<int> d(n + 1);
    for (int i = 1; i <= n; i++) {
        fin >> d[i];
    }

    vector<int> tmp = d;
    sort(tmp.begin() + 1, tmp.end());
    tmp.erase(unique(tmp.begin() + 1, tmp.end()), tmp.end());

    vector<Query> qs(q);
    for (int i = 0; i < q; i++) {
        fin >> qs[i].x >> qs[i].p;
        qs[i].id = i;
    }
    sort(all(qs));

    SegTree seg(tmp);
    vector<int> ans(q);
    int ptr = 0;

    for (int i = 1; i <= n; i++) {
        int pos = lower_bound(tmp.begin() + 1, tmp.end(), d[i]) - tmp.begin();
        seg.update(1, 1, seg.n, pos, d[i]);
        while (ptr < q && qs[ptr].x == i) {
            ans[qs[ptr].id] = seg.query(1, 1, seg.n, qs[ptr].p);
            ptr++;
        }
    }

    for (int i = 0; i < q; i++) {
        printf("%lld\n", ans[i]);
    }

    return 0;
}