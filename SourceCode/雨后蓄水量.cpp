/*
    @ Author:       Eric / Sky__White
    @ Filename:     trapping_rain_water.cpp
    @ Date:         25/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>

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

struct Pmax {
    set<pair<int,int> > S;
    int n, sum;
    Pmax(int N = 0) : n(N), sum(0) {}

    void reset(int N) { S.clear(); n = N; sum = 0; }

    void update(int pos, int val) {
        auto it = S.lower_bound({pos, 0});
        int L = 0;
        auto pv = S.end();
        if (it != S.begin()) { pv = prev(it); L = pv->second; }

        if (val <= L) return;

        if (pv != S.end()) {
            int nxp = (it != S.end()) ? it->first : n + 1;
            sum -= pv->second * (nxp - pv->first);
        }

        auto cur = it;
        while (cur != S.end() && cur->second < val) {
            auto ne = next(cur);
            int nxp = (ne == S.end()) ? n + 1 : ne->first;
            sum -= cur->second * (nxp - cur->first);
            cur = S.erase(cur);
        }
        auto kk = cur;

        S.insert({pos, val});
        if (pv != S.end())
            sum += pv->second * (pos - pv->first);
        int nxp2 = (kk != S.end()) ? kk->first : n + 1;
        sum += val * (nxp2 - pos);
    }
};

signed main() {
    // freopen("rain.in", "r", stdin);
    // freopen("rain.out", "w", stdout);

    int T; fin >> T;
    
    while (T -- ) {
        int n; fin >> n;
        vector<int> a(n + 1);
        int sum_a = 0, max_a = 0;
        for (int i = 1; i <= n; i ++ ) {
            fin >> a[i];
            sum_a += a[i];
            max_a = max(max_a, a[i]);
        }

        Pmax Pf(n), Pg(n);
        for (int i = 1; i <= n; i ++ ) {
            Pf.update(i, a[i]);
            Pg.update(n + 1 - i, a[i]);
        }

        int q; fin >> q;
        while (q -- ) {
            int x, v; fin >> x >> v;
            a[x] += v;
            sum_a += v;
            max_a = max(max_a, a[x]);
            Pf.update(x, a[x]);
            Pg.update(n + 1 - x, a[x]);

            int ans = Pf.sum + Pg.sum - sum_a - n * max_a;
            printf("%lld\n", ans);
        }
    }
    return 0;
}