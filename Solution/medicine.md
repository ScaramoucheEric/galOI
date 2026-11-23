# 信友队 Problem ID: 24540 medicine

## 题目大意：
小信是一个药剂师，商店里面有 $n$ 种魔法材料。第 $i$ 种材料的魔力值为 $d_i$，每升价格为 $p_i$，每瓶魔法药水最多使用 $l_i$ 升第 $i$ 种药水。

现在有 $m$ 个顾客前来调配药水，每个顾客都希望小信用商店里的材料调配成一瓶混合药水（可以单一材料）。第 $j$ 个顾客要求药水的总价格不超过 $g_j$，总体积不小于 $L_j$。在这些限制条件下，顾客希望药水的魔力值尽可能高。一瓶混合药水的魔力值等于所有参与调配的材料的魔力值的最小值。请你计算每个顾客能买到的最高魔力值的药水。如果无法满足他的需求，则输出 $-1$。

对于所有的测试数据，保证 $n,m \le 100000$，$1 \le d_i, p_i, l_i \le 10^5$，$1 \le g_j, L_j \le 10^{18}$。

|测试点编号|$n$ =| $m$ = | 其他限制 |
| :----: | :-----: | :-----: | :--: |
| $1,2,3$ | $10$ | $10$ | 无 |
| $4,5,6$ | $500$ | $500$ | 无 |
| $7,8,9$ | $5000$ | $5000$ | 无 |
| $10,11,12$ | $100000$ | $100000$ | $p_i = 1$ |
| $13,14,15$ | $100000$ | $100000$ | $l_i = 1$ |
| $16,17,18,19,20$ | $100000$ | $100000$ | 无 |

## 45pts:
我们注意到，在合成药水的材料中，选取最小的魔力值成为药水的魔力值，最大化这个值，即为「最大的最小值」问题，所以想到二分。而这一题的可二分性是显然的。

于是我们二分魔力值 $d$，那么超过 $d$ 的魔法材料都是可选的。这么说我们只需要在这些魔法材料中找最便宜的 $L_j$ 个买，就行了。考虑用 `priority_queue` 维护 $p_i$ 最小的那些魔法材料，取 $L_j$ 个判断有没有超过 $g_j$ 元就行了。

时间复杂度为 $O(mn \log \max\limits_{1 \le j \le m}{g})$，可得 $45pts$。

### code(C++)

```cpp
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <cstdio>
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

using namespace std; Read fin;

const int Mod = 1e9 + 7;

signed main() {
    freopen("medicine.in", "r", stdin);
    freopen("medicine.out", "w", stdout);

    int n, m; fin >> n >> m;

    struct Medicine {
        int d, p, l;

        bool operator < (const Medicine & W) const {
            return p > W.p;
        }
    }; vector<Medicine> me(n + 1);

    int up = 0;
    for (int i = 1; i <= n; i ++ ) {
        fin >> me[i].d >> me[i].p >> me[i].l;
        up = max(up, me[i].d);
    }

    sort(1 + all(me), [&](Medicine A, Medicine B) {
        return A.d > B.d;
    });

    // for (int i = 1; i <= n; i ++ )
    //     cout << me[i].d << " " << me[i].p << " " << me[i].l << endl;
    // cout << endl << endl;
    
    while(m -- ) {
        int g, L; fin >> g >> L;
        int gg = g, LL = L;
        
        int l = 0, r = up, res = 0;
        
        function<bool(int)> judge = [&](int mid) -> bool {
            priority_queue<Medicine> q;
            
            for (int i = 1; i <= n; i ++ ) {
                if (me[i].d < mid) break;
                q.push(me[i]);
                // cout << i << " ";
            }
            // cout << endl;

            while(q.size()) {
                Medicine A = q.top(); q.pop();
                // cout << "g = " << g << ", L = " << L << endl;
                if (A.l <= L) {
                    g -= A.l * A.p;
                    L -= A.l;
                } else {
                    g -= L * A.p;
                    L = 0;
                }
                
                // cout << "g' = " << g << ", L' = " << L << endl;

                // printf("l = %lld, p = %lld, d = %lld\n", A.l, A.p, A.d);

                if (L == 0) break;
            }

            // cout << mid << " ";

            if (g < 0 or L > 0) return false;
            return true;
        };

        while(l <= r) {
            int mid = l + r >> 1;

            if (judge(mid)) {
                // cout << "YES" << endl;
                l = mid + 1;
                res = mid;
            } else {
                // cout << "NO" << endl;
                r = mid - 1;
            }
            g = gg, L = LL;
        }

        if (res)
            cout << res << endl;
        else
            cout << -1 << endl;
        
        // cout << endl;
    }
}
```

## 说完45pts，我们考虑怎么优化成100pts的

我们发现，上面的思虑时间复杂度的瓶颈在于每次二分 $d$ 之后，都必须手动把符合条件的材料加到`priority_queue`里面。那么有没有既简单又好上手的数据结构可以代替呢？

#### ~~***有的，兄弟，有的！***~~

我们 ~~**不难**~~ 想到有个叫可持久化线段树的东西。为什么会想到TA呢？

因为可二分的题目一定具有单调性，我们按 $d$ 从小到大看，发现每次操作会加上在原本的优先队列里加上 $l_i$ 个价值为 $p_i$ 的魔法材料。而我们需要的是价值最小的 $L_j$ 个魔法材料。那么这个操作显然可以用可持久化线段树（值域线段树）储存这个信息。

我们先将每一种魔法材料按 $p_i$ 从小到大排序，然后按照顺序加到可持久化线段树中。在二分的时候，直接二分线段树的每个版本，接下来应该都会写了。

时间复杂度为 $O(m\log n\cdot \log 1e5)$，$1e5$ 是值域，$\log 1e5$ 大约是 $16.61$。常数小到飞起！！

### 注意：可持久化线段树用`vector`写的时候注意`push_back()`的时候会更改指针位置，所以千万要注意移元顶针！！！

### code

```cpp
/*
    @ Author:       Eric / Sky__White
    @ Filename:     password.cpp
    @ Date:         11/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <cstdio>
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

using namespace std; Read fin;

const int Mod = 1e9 + 7;

class SegTree {
    public:
    struct Node {
        int l, r, s, sum;
    }; vector<Node> t;
    vector<int> root;

    void insert(int &p, int pre, int l, int r, int price, int limit) {
        t.push_back(t[pre]);
        p = t.size() - 1;
        t[p].s += limit, t[p].sum += price * limit;

        if (l == r) {
            // cout << "t[p].s = " << t[p].s << endl;

            return ;
        }

        int mid = l + r >> 1;

        if (price <= mid) {
            int new_l, old_l = t[p].l;
            insert(new_l, t[pre].l, l, mid, price, limit);
            t[p].l = new_l;
        } else {
            int new_r, old_r = t[p].r;
            insert(new_r, t[pre].r, mid + 1, r, price, limit);
            t[p].r = new_r;
        }
    }

    int query(int p, int l, int r, int limit) {
        if (l == r) {
            // cout << "r, limit = " << r << " " << limit << endl;
            return r * limit;
        }
        int mid = l + r >> 1;
        // cout << "t[t[p].l].s = " << t[t[p].l].s << endl;
        if (t[t[p].l].s >= limit) { 
            // cout << "left: l = " << l << "; r = " << r << endl;
            return query(t[p].l, l, mid, limit); 
        } else { 
            // cout << "right: l = " << l << "; r = " << r << endl; 
            return t[t[p].l].sum + query(t[p].r, mid + 1, r, limit - t[t[p].l].s); 
        }
    }
};

signed main() {
    freopen("medicine.in", "r", stdin);
    freopen("medicine.out", "w", stdout);
    int n, m; fin >> n >> m;

    struct Node {
        int d, p, l;
    }; vector<Node> arr(n + 1);

    for (int i = 1; i <= n; i ++ ) {
        fin >> arr[i].d >> arr[i].p >> arr[i].l;
    }

    sort(1 + all(arr), [&](Node a, Node b){
        return a.d > b.d;
    });

    SegTree T; T.root.resize(n + 1); T.t.push_back({0, 0, 0, 0});

    for (int i = 1; i <= n; i ++ ) {
        // cout << "arr[i].l = " << arr[i].l << endl;
        T.insert(T.root[i], T.root[i - 1], 1, 1e5, arr[i].p, arr[i].l);
    }

    while(m -- ) {
        int g, lim; fin >> g >> lim;

        // cout << g << " " << lim << endl;

        int l = 1, r = n, res = -1;

        while(l <= r) {
            int mid = l + r >> 1;
            // cout << l << " " << r << " -> " << mid << endl;

            if (T.query(T.root[mid], 1, 1e5, lim) <= g and T.t[T.root[mid]].s >= lim) {
                r = mid - 1;
                res = mid;
                // cout << T.query(T.root[mid], 1, 1e5, lim) << " " << T.t[T.root[mid]].s << endl;
            } else {
                l = mid + 1;
                // cout << T.query(T.root[mid], 1, 1e5, lim) << " " << T.t[T.root[mid]].s << endl;
            }
        }

        if (res != -1)
            cout << arr[res].d << endl;
        else cout << -1 << endl;

        // cout << endl << endl;
    }
}
```