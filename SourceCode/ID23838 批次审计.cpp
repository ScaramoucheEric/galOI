/*
    @ Author:       Eric / Sky__White
    @ Filename:     ID23838 批次审计.cpp
    @ Date:         06/19/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
#include <deque>
#include <set>

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
using namespace std; Read fin;

#define int long long
#define all(a) a.begin(), a.end()

const int INF = (1LL << 60);

struct SegTree {
    int n;
    vector<multiset<int> > leaf;
    vector<int> t;
    SegTree(int sz = 0) {
        n = 1;
        while (n < sz) n <<= 1;
        leaf.resize(2 * n);
        t.assign(2 * n, INF);
    }
    void pull(int pos) {
        t[pos] = min(t[pos << 1], t[pos << 1 | 1]);
    }
    void newn(int pos) {
        if (leaf[pos].empty()) t[pos] = INF;
        else t[pos] = *leaf[pos].begin();
    }
    void insert(int pos, int val) {
        pos += n;
        leaf[pos].insert(val);
        newn(pos);
        pos >>= 1;
        while (pos) {
            pull(pos);
            pos >>= 1;
        }
    }
    void erase(int pos, int val) {
        pos += n;
        auto it = leaf[pos].find(val);
        if (it != leaf[pos].end()) {
            leaf[pos].erase(it);
            newn(pos);
            pos >>= 1;
            while (pos) {
                pull(pos);
                pos >>= 1;
            }
        }
    }
    int query(int l, int r) {
        if (l > r) return INF;
        l += n;
        r += n;
        int res = INF;
        while (l <= r) {
            if (l & 1) res = min(res, t[l ++ ]);
            if (!(r & 1)) res = min(res, t[r -- ]);
            l >>= 1;
            r >>= 1;
        }
        return res;
    }
};

signed main() {
    int n, k;
    fin >> n >> k;
    string s;
    cin >> s;
    vector<int> w(n + 1);
    for (int i = 1; i <= n; i ++ ) fin >> w[i];

    vector<int> pre(n + 1, 0);
    for (int i = 1; i <= n; i ++ ) {
        int v = (s[i - 1] == 'A') ? w[i] : -w[i];
        pre[i] = pre[i - 1] + v;
    }

    vector<int> vals = pre;
    sort(all(vals));
    vals.erase(unique(all(vals)), vals.end());
    int m = vals.size();

    auto getR = [&](int x) {
        return (int)(lower_bound(all(vals), x) - vals.begin()) + 1;
    };

    SegTree t1(m + 2), t2(m + 2);

    vector<int> dp(n + 1, INF);
    dp[0] = 0;

    deque<int> dq;

    int r0 = getR(pre[0]);
    t1.insert(r0, dp[0]);
    t2.insert(r0, dp[0]);
    dq.push_back(0);

    for (int i = 1; i <= n; i ++ ) {
        while (!dq.empty() && dq.front() < i - k) {
            int j = dq.front();
            int rj = getR(pre[j]);
            t1.erase(rj, dp[j]);
            t2.erase(rj, dp[j]);
            dq.pop_front();
        }

        int ri = getR(pre[i]);

        int best1 = t1.query(1, ri - 1);
        int best2 = t2.query(ri, m);

        if (best2 < INF) best2 += 1;

        dp[i] = min(best1, best2);

        t1.insert(ri, dp[i]);
        t2.insert(ri, dp[i]);
        
        dq.push_back(i);
    }

    cout << dp[n] << endl;
    return 0;
}