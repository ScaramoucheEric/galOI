/*
    @ Author:       Eric / Sky__White
    @ Filename:     山田凉的片段.cpp
    @ Date:         14/11/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <functional>
#include <queue>

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
#define endl "\n"
#define IO(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout);

using namespace std; Read fin;

class SegTree {
    public:
    struct Node {
        int l, r, res, lazy;
    }; vector<Node> t;
    const Node Null = {0,0,0,0};
    const int root = 1;

    void init(int n) {
        t.reserve(n + 1 << 1);
        t.push_back(Null);
        t.push_back(Null);
    }

    int make() {
        t.push_back(Null);
        return t.size() - 1;
    }

    void push_up(int p) {
        t[p].res = t[t[p].l].res + t[t[p].r].res;
    }

    int insert(int p, int l, int r, int x) {
        if (!p) p = make();

        if (l == r) {
            t[p].res = 1;
            return p;
        }

        int mid = l + r >> 1;
        if (x <= mid) { int tt = insert(t[p].l, l, mid, x); t[p].l = tt; }
        if (x  > mid) { int tt = insert(t[p].r, mid + 1, r, x); t[p].r = tt; }

        push_up(p);

        return p;
    }

    int query(int p, int l, int r, int L, int R) {
        if (!p) return 0;
        if (L > R) return 0;

        if (L <= l and r <= R) {
            return t[p].res;
        }

        int mid = l + r >> 1, res = 0;

        if (L <= mid) res += query(t[p].l, l, mid, L, R);
        if (R  > mid) res += query(t[p].r, mid + 1, r, L, R);

        return res;
    }
};

signed main() {
    int n; fin >> n;

    vector<int> arr(n + 1);

    for (int i = 1; i <= n; i ++ ) {
        fin >> arr[i];
    }

    SegTree T; T.init(n);

    int l = 1, r = 1;

    int cnt = 0;

    while(r <= n) {
        if (r < n and arr[r + 1] < arr[r]) {
            while(l <= r) {
                T.insert(1, 1, 1e6, arr[l]);
                l ++ ;
            }
            cnt ++ ;
            // cout << l << " " << r << endl;
        } else if (T.query(1, 1, 1e6, arr[l] + 1, arr[r] - 1) != 0) {
            while(l <= r) {
                T.insert(1, 1, 1e6, arr[l]);
                l ++ ;
            }
            cnt ++ ;
            // cout << l << " " << r << endl;
        }
        r ++ ;
    }

    if (l <= n) {
        while(l <= r) {
            T.insert(1, 1, 1e6, arr[l]);
            l ++ ;
        }
        cnt ++ ;
    }

    cout << cnt << endl;
}