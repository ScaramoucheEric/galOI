/*
    @ Author:       Eric / Sky__White
    @ Filename:     ship.cpp
    @ Date:         14/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <cstdio>
#include <unordered_map>
#include <queue>
#include <map>
#include <set>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("O2")
#pragma GCC optimize("O3")

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

const int INF = 0x3f3f3f3f3f3f3f3f;

struct Node {
    int x, yl, yr;
    int val;
    bool operator<(const Node& other) const {
        if (x != other.x) return x < other.x;
        return val < other.val;
    }
};

struct BIT {
    int n;
    vector<int> tree;
    BIT(int size) : n(size), tree(size + 2, 0) {}
    
    void add(int pos, int val) {
        for (; pos <= n; pos += pos & -pos)
            tree[pos] += val;
    }
    
    int query(int pos) {
        int res = 0;
        for (; pos > 0; pos -= pos & -pos)
            res += tree[pos];
        return res;
    }
};

struct SegTree {
    int n;
    
    struct Node {
        int l, r, res, lazy;
    }; vector<Node> t;

    #define lc (p << 1)
    #define rc (p << 1 | 1)
    
    SegTree(int N) : n(N) {
        t.resize((n + 1 << 2) + 1);
        build(1, 1, n);
    }

    void build(int p, int l, int r) {
        t[p].l = l, t[p].r = r;
        if (l == r) {
            t[p].res = 0;
            return ;
        }

        int mid = l + r >> 1;

        build(lc, l, mid), build(rc, mid + 1, r);

        push_up(p);
    }

    void push_up(int p) {
        t[p].res = max(t[lc].res, t[rc].res);
    }

    void push_down(int p) {
        if (t[p].lazy == 0) return ;
        t[lc].lazy += t[p].lazy;
        t[rc].lazy += t[p].lazy;
        t[lc].res += t[p].lazy;
        t[rc].res += t[p].lazy;
        t[p].lazy = 0;
    }

    void update(int p, int l, int r, int k) {
        if (t[p].l >= l and t[p].r <= r) {
            t[p].res += k;
            t[p].lazy += k;
            return ;
        }
        push_down(p);

        int mid = t[p].l + t[p].r >> 1;

        if (l <= mid) update(lc, l, r, k);
        if (r >  mid) update(rc, l, r, k);

        push_up(p);
    }

    int query(int p, int l, int r) {
        if (t[p].l >= l and t[p].r <= r) {
            return t[p].res;
        }

        push_down(p);

        int mid = t[p].l + t[p].r >> 1, res = -INF;

        if (l <= mid) res = max(res, query(lc, l, r));
        if (r >  mid) res = max(res, query(rc, l, r));

        return res;
    }

    int maxv() {
        return t[1].res;
    }
};

void solve() {
    int n; fin >> n;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++ ) {
        fin >> a[i];
    }
    
    BIT bit(n);
    int inv = 0;
    for (int i = n; i >= 1; i--) {
        inv += bit.query(a[i] - 1);
        bit.add(a[i], 1);
    }
    if (inv == 0) {
        puts("0");
        return ;
    }
    
    vector<pair<int, int>> P;
    P.emplace_back(0, 0);
    int max_val = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] > max_val) {
            max_val = a[i];
            P.emplace_back(i, a[i]);
        }
    }

    int m = (int)P.size() - 1;
    
    vector<pair<int, int> > Q;
    Q.emplace_back(0, 0);

    int min_val = n + 1;
    for (int i = n; i >= 1; i -- ) {
        if (a[i] < min_val) {
            min_val = a[i];
            Q.emplace_back(i, a[i]);
        }
    }
    // reverse(1 + all(Q));
    int t = Q.size() - 1;
    
    vector<int> P_pos(m + 1), P_val(m + 1);
    vector<int> Q_pos(t + 1), Q_val(t + 1);

    for (int i = 1; i <= m; i++) {
        P_pos[i] = P[i].first;
        P_val[i] = P[i].second;
    }
    for (int i = 1; i <= t; i++) {
        Q_pos[i] = Q[t - i + 1].first;
        Q_val[i] = Q[t - i + 1].second;
    }

    // sort(1 + all(Q_pos));
    // sort(1 + all(Q_val));
    
    vector<Node> node;
    
    for (int k = 1; k <= n; k++) {
        int val = a[k];
        
        int l = lower_bound(P_pos.begin() + 1, P_pos.end(), k) - P_pos.begin() - 1;
        if (l < 1) continue;
        
        int p_s = upper_bound(P_val.begin() + 1, P_val.begin() + l + 1, val) - P_val.begin();
        if (p_s > l) continue;
        
        int r = upper_bound(Q_pos.begin() + 1, Q_pos.end(), k) - Q_pos.begin();
        if (r > t) continue;

        int q_e = lower_bound(Q_val.begin() + r, Q_val.end(), val) - Q_val.begin() - 1;
        if (q_e < r) continue;

        node.push_back({p_s, r, q_e, 2});
        node.push_back({l + 1, r, q_e, -2});
    }
    
    for (int pi = 1; pi <= m; pi ++ ) {
        int p_pos = P_pos[pi];
        int p_val = P_val[pi];
        
        int q_l = upper_bound(Q_pos.begin() + 1, Q_pos.end(), p_pos) - Q_pos.begin();
        if (q_l > t) continue;
        
        int q_r = lower_bound(Q_val.begin() + 1, Q_val.end(), p_val) - Q_val.begin() - 1;
        if (q_r < q_l) continue;
        
        node.push_back({pi, q_l, q_r, 1});
        node.push_back({pi + 1, q_l, q_r, -1});
    }
    
    sort(all(node));
    SegTree seg(n);

    int max_g = 0;
    int j = 0, tot = node.size();
    
    for (int x = 1; x <= m; x++) {
        while (j < tot and node[j].x == x) {
            seg.update(1, node[j].yl, node[j].yr, node[j].val);
            j ++ ;
        }
        max_g = max(max_g, seg.maxv());
    }
    
    int ans = min(inv, inv - max_g + 1);
    cout << ans << endl;
}

signed main() {
    // freopen("ship.in", "r", stdin);
    // freopen("ship.out", "w", stdout);
    
    int T; fin >> T;

    while (T -- ) {
        solve();
    }
    return 0;
}