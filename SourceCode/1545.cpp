/*
    @ Author:       Eric / Sky__White
    @ Filename:     1545.cpp
    @ Date:         20/07/2026
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
        int l, r, res;
    }; vector<Node> t;

    int make() {
        t.push_back({0, 0, INF});
        return t.size() - 1;
    }

    int insert(int p, int l, int r, int x, int k) {
        if (!p) p = make();
        
        if (l == r and l == x) {
            t[p].res = k;
            return p;
        } else if (l == r) {
            return p;
        }

        int mid = l + r >> 1;

        if (x <= mid) t[p].l = insert(t[p].l, l, mid, x, k);
        if (x >  mid) t[p].r = insert(t[p].r, mid + 1, r, x, k);

        t[p].res = min(t[t[p].l].res, t[t[p].r].res);

        return p;
    }

    int query(int p, int l, int r, int L, int R) {
        if (!p) return INF;
        if (L > R) return INF;
        if (l >= L and r <= R) {
            return t[p].res;
        }

        int mid = l + r >> 1, res = INF;
        if (L <= mid) res = min(res, query(t[p].l, l, mid, L, R));
        if (R >  mid) res = min(res, query(t[p].r, mid + 1, r, L, R));

        return res;
    }
};

signed main() {
    int n, l; fin >> n >> l; int a, b; fin >> a >> b;

    vector<bool> flag(l + 1);
    vector<int> dp(l + 1, INF);

    dp[0] = 0;

    for (int i = 1; i <= n; i ++ ) {
        int s, e; fin >> s >> e;

        for (int j = s + 1; j < e; j ++ )
            flag[j] = true;
    }

    SegTree T; T.t.push_back({0, 0, INF}); T.t.push_back({0, 0, INF});

    T.insert(1, 0, l, 0, 0);
    
    for (int i = 2; i <= l; i += 2) { // 只能tm放在偶数上
        if (flag[i]) continue;

        int L = max(0ll, i - b * 2);
        int R = i - a * 2;
        if (R >= 0 && L <= R) {
            dp[i] = min(dp[i], T.query(1, 0, l, L, R) + 1);
        }
        T.insert(1, 0, l, i, dp[i]);
    }

    // for (int i = 0; i <= l; i ++ )
    //     cout << dp[i] << " \n"[i == l];

    if (dp[l] >= INF) {
        cout << -1 << endl;
    } else {
        cout << dp[l] << endl;
    }
}