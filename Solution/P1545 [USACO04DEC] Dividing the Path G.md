# P1545 [USACO04DEC] Dividing the Path G

## 题目简述

现在有一段长为 $L$（ $L$ 是一个偶数）的草地，现在你可以设置喷水装置，射程为 $[A, B]$，给定 $n$ 个区间 $[S_i, E_i]$ 表示一些草坪只能被一个喷水装置浇到。询问要使每一处草地都被浇到且符合条件的最小喷水装置的数量。

若存在无解的，输出`-1`。
注意：

> 1. 数轴 $L$ 从 $0$ 开始标记（即坐标范围 $0\sim L$）  
> 2. 喷灌器坐标和射程必须为整数，对于坐标为 $i$ 射程为 $x$ 的喷灌器，它的灌溉范围为 $[i-x,i+x]$。
> 3. 浇灌区间必须在山脊范围内。例如，不能在 $0$ 位置放一个半径为 $1$ 的浇灌器。

寻找最少需要的喷灌器数目。

## 说明/提示

对于 $100\%$ 的数据，$1\le L\le 10^6$，$1\le A,B\le 10^3$，$1\le N\le 10^3$，$1\le S_i<E_i\le L$。

## 暴力DP

首先不难想到十分暴力的dp做法。我们把 $[i-x, i+x]$ 的浇灌范围不妨看作 $[j-2x, j]$ 的区间。

设置dp状态：$dp_i$ 表示前 $i$ 个草地被浇的最少装置数。由于 $[S_i, E_i]$ 的草地只能由一个装置浇灌，也就是说区间 $[S_i + 1, E_i - 1]$ 是不允许放置装置的。这边直接暴力标记 $st$ 即可，时间来得及。那么不难想到递推方程式:
$$dp_i \leftarrow \min\limits_{j = 0}^{i - 1}dp_{j}[j \equiv 0 \pmod 2 \And st_j=False]$$

那么这么做恭喜你，拿到了高分90pts。~~数据好水啊，~~ 题目给了我们很多的部分分，作者大大真好 ~~（bushi~~

[这是90pts记录](https://www.luogu.com.cn/record/287389352)

那么考虑怎么优化了。~~为了高贵的100pts，进击！~~

## 优化DP

刚才的DP显而易见是 $O(n^2)$ 的。瓶颈时取最小值操作。那么横简单，直接一个线段树或者维护一个单调队列即可。

我是选择~~可愛いの~~线段树啦～～

## Code

```cpp
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
    
    for (int i = 2; i <= l; i += 2) {
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
```