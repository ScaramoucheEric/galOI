/*
    @ Author:       Eric / Sky__White
    @ Filename:     P4113.cpp
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

class BIT {
    public:
    vector<int> arr;

    BIT(int n) {
        arr.resize(n + 1);
    }

    int lowbit(int x) {
        return x & -x;
    }

    void add(int x, int k) {
        while(x < arr.size()) {
            arr[x] += k;
            x += lowbit(x);
        }
    }

    int query(int r) {
        int res = 0;
        while(r) {
            res += arr[r];
            r -= lowbit(r);
        }

        return res;
    }

    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

signed main() {
    int n, m, q; fin >> n >> m >> q;
    vector<int> arr(n + 1);

    for (int i = 1; i <= n; i ++ ) fin >> arr[i];

    struct query {
        int l, r, id, res;
    };

    vector<query> Q(q + 1);

    for (int i = 1; i <= q; i ++ ) fin >> Q[i].l >> Q[i].r, Q[i].id = i;

    sort(1 + all(Q), [&](query a, query b) {
        return a.r < b.r;
    });

    int pos = 1;
    unordered_map<int, int> last;
    vector<int> pre(n + 1, -1);

    BIT t(n);

    for (int i = 1; i <= n; i ++ ) {
        if (last.count(arr[i]) == 0) {
            pre[i] = -1;
        } else {
            pre[i] = last[arr[i]];
        }

        if (pre[i] != -1 and pre[pre[i]] != -1) {
            t.add(pre[pre[i]], -1);
        }
        if (pre[i] != -1)
            t.add(pre[i], 1);

        while (pos <= q and i == Q[pos].r) {
            Q[pos].res = t.query(Q[pos].l, Q[pos].r);
            pos ++ ;
        }

        last[arr[i]] = i;
    }

    sort(1 + all(Q), [&](query a, query b){
        return a.id < b.id;
    });

    for (int i = 1; i <= q; i ++ )
        printf("%lld\n", Q[i].res);

    return 0;
}