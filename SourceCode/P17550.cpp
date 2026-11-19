#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <functional>
#include <cstdio>
#include <map>
#include <vector>

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
#define endl "\n"

using namespace std; Read fin;

using PII = pair<int, int> ;

const int INF = 0x3f3f3f3f3f3f3f3f;

class SegTree {
    public:
        struct Node {
            int l, r, maxx;
        }; vector<Node> t;
        const Node Null = {0, 0, 0};

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
            t[p].maxx = max(t[t[p].l].maxx, t[t[p].r].maxx);
        }

        int insert(int p, int l, int r, int x, int k) {
            if (!p) p = make();
            
            if (l == r and l == x) {
                t[p].maxx = k;
                return p;
            }

            int mid = l + r >> 1;

            if (x <= mid) { int tt = insert(t[p].l, l, mid, x, k); t[p].l = tt; }
            if (x >  mid) { int tt = insert(t[p].r, mid + 1, r, x, k); t[p].r = tt; }

            push_up(p);

            return p;
        }

        int query(int p, int l, int r, int L, int R) {
            if (!p) return p;

            if (L <= l and r <= R) return t[p].maxx;

            int mid = l + r >> 1, res = 0;

            if (L <= mid) res = max(res, query(t[p].l, l, mid, L, R));
            if (R >  mid) res = max(res, query(t[p].r, mid + 1, r, L, R));

            return res;
        }
};

void solve() {
    int n, m, k; fin >> n >> m >> k;

    vector<int> p(n + 1);

    SegTree T;

    T.init(n);

    for (int i = 1; i <= n; i ++ )
        fin >> p[i];

    vector<int> pre(n + 1);

    for (int i = 1; i <= n; i ++ ) {
        pre[i] = pre[i - 1] + p[i];
    }

    vector<int> dp(n + 1);

    vector<vector<int> > L(n + 1);

    for (int i = 1; i <= m; i ++ ) {
        int l, r; fin >> l >> r;
        L[r].push_back(l);
    }

    for (int i = 1; i <= n; i ++ ) {
        dp[i] = dp[i - 1];
        for (auto j : L[i])
            dp[i] = max(dp[i], dp[j - 1] + pre[i] - pre[j - 1]);
    }

    cout << dp[n] * k << endl;
}

signed main(){
    #ifndef ONLINE_JUDGE
    IO("P17550");
    #endif

    int T; fin >> T;

    while(T -- ) {
        solve();
    }
}