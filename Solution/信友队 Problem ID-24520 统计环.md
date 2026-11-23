# 统计环

> 时间限制：6000ms  /  空间限制：512MB
> 
> 输入输出：cycle.in/cycle.out

这题是[Codeforces 11D](https://codeforces.com/problemset/problem/11/D)的强化版。没有信友队题库的可以把这道题的代码交到CF上。

## 题目简述

给定一张 $N$ 个节点，$M$ 条边的图，图中不含自环，但可以含重边。你需要统计简单环的数量，输出答案对`998244353`取余的结果。

对，题目就这么简单。

## 数据范围：

 - $2 \le N \le 20$
 - $2 \le M \le 2 \times 10^5$
 - $1 \le U_i < V_i \le N$
 - 所有输入值皆为整数。~~（当然这句是废话）~~
 - Subtask 1（30 pts）：$N \le 10$
 - Subtask 2（20 pts）：$N \le 18$
 - Subtask 2（50 pts）：$N \le 20$

[大样例（24520.zip）](https://staticw.turingstar.com.cn/202607261943/5280eee70a9bb6f8a294b4117228272d/79607d00-c258-40a7-8195-965da5d3f4d5)

## 思路

### 50pts

我们发现 $N$ 很小，我们考虑直接状压DP。**环是比较难维护的，所以我们考虑维护一条链。**$dp_{S,i,j}$ 中，$S$ 表示我们现在选了多少个点，$i$、$j$ 表示这条链的两端分别是 $i$ 和 $j$。$dp_{S,i,j}$ 表示现在这个情况下有多少条符合条件的链。对于每个状态，我们可以转移：

![](https://images.cnblogs.com/cnblogs_com/blogs/868669/galleries/2523722/o_260726235802_ScreenShot_2026-07-26_203114_892.png)

首先左边转移：

$$dp_{S | (1 << k), k, j} \leftarrow dp_{S, i, j} cdot cnt_{i, k}$$

同理右边转移：

$$dp_{S | (1 << k), i, k} \leftarrow dp_{S, i, j} \cdot cnt_{j, k}$$

之后我们就可以 $O(2^N \cdot N^3)$ 得做完这题的 50 分了。时间限制很宽，足足 6s。

### 100pts

我们通过上面的DP方程式，感觉向两边拓展还是太吃操作了，有没有简单又实用的方法呢？

**有的兄弟，用的！**

我们考虑钦定左端点为环上编号最大的一个点，即 $\lfloor \log_2 S \rfloor$。这样我们止血药考虑右端点的转移了。新的DP状态为 $dp_{S, i}$，表示含有 $S$ 的节点，右端点为 $i$ 所有符合条件的可行的数量。

$$dp_{S | (1 << k), k} \leftarrow dp_{S, i} \cdot cnt_{i, k}$$

最后统计答案，就是把符合条件的链找一下左端点和右端点，乘上连接两个点的边的数量，即：

$$ans \leftarrow dp_{S, i} * cnt_{\lfloor \log_2 S \rfloor, i}$$

这样我们就得到了一个 $O(2^N \cdot N^2)$ 的做法了，跑起来飞飞的。

PS:

> 注意一种情况，就是两个点在一条边上来回串。这些加起来，简单算一下，刚好等于 $m$，最后要减去。
>
> 由于每一个环，我们都算了 2 遍，需要把答案除以 2。
> 
> 最后不要忘了模除`998244353`。

Code:
```cpp
/*
    @ Author:       Eric / Sky__White
    @ Filename:     统计环.cpp
    @ Date:         15/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <functional>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
#include <queue>
#include <ctime>

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

const int Mod = 998244353;

signed main() {
    freopen("circle.in", "r", stdin);
    freopen("circle.out", "w", stdout);

    int n, m; fin >> n >> m;
    auto cl = clock();

    vector<vector<int> > G(n + 1);
    vector<vector<int> > cnt(n + 1, vector<int>(n + 1));

    for (int i = 1; i <= m; i ++ ) {
        int u, v; fin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
        cnt[u][v] ++ , cnt[v][u] ++ ;
    }

    vector<vector<int> > dp(1 << n, vector<int>(n + 1));
    
    for (int i = 1; i <= n; i ++ )
        dp[1 << i - 1][i] = 1;

    for (int S = 1; S < 1 << n; S ++ ) {
        int rt = log2(S) + 1.000000003; // 小心有误差 QwQ

        for (int u = 1; u <= rt; u ++ ) {
            if (S & (1 << u - 1)) /* u 在 S 里面 */ for (int v = 1; v <= rt; v ++ )
                if (~S & (1 << v - 1)) { // 拓展的 v 不能出现在 S 里面
                    (dp[S | (1 << v - 1)][v] += dp[S][u] * cnt[u][v]) %= Mod;
                }
        }
    }

    int ans = 0;

    function<int(int)> lowbit = [&](int x) -> int {
        return x & -x;
    };

    for (int S = 1; S < 1 << n; S ++ ) {
        int rt = log2(S) + 1.000000003; // 这里也是QwQ 血的教训 QwQ
        if (S - lowbit(S) == 0) continue;

        for (int u = 1; u <= rt; u ++ ) {
            int &v = rt;

            if (u == v) continue;
            if (~S & (1 << u - 1)) continue; // 看一下 u 在不在 S 里面
            (ans += dp[S][u] * cnt[u][v]) %= Mod;
        }
    }

    ans = (ans - m + Mod) % Mod;

    (ans *= 499122177) %= Mod;

    while((clock() * 1.0 - cl) / CLOCKS_PER_SEC < 5.99) ; // 卡评测机 xixi

    cout << ans << endl;
}
```