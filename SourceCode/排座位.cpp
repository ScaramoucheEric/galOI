/*
    @ Author:       Eric / Sky__White
    @ Filename:     排座位.cpp
    @ Date:         30/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <list>

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
#define IO(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout);

using namespace std; Read fin;

const int INF = 0x3f3f3f3f3f3f3f3f;

class BIT {
    public:
    vector<int> arr;
    BIT(int n) : arr(n + 1) {}
    int lowbit(int x) { return x & -x; }
    void add(int x, int v) { for (; x < arr.size(); x += lowbit(x)) arr[x] += v; }
    int query(int x) { int res = 0; for (; x; x -= lowbit(x)) res += arr[x]; return res; }
    int query(int l, int r) { return query(r) - query(l - 1); }
};

signed main() {
    int n; fin >> n;

    vector<int> seat(n + 1);
    vector<int> geust(n + 1);
    vector<int> L(n + 1, INF), R(n + 1);

    for (int i = 1; i <= n; i ++ ) {
        fin >> seat[i];
        L[seat[i]] = min(L[seat[i]], i);
        R[seat[i]] = max(R[seat[i]], i);
    }

    vector<int> res(n + 1);

    BIT T(n);

    vector<list<int> > tab(n + 1);
    vector<vector<int> > g(n + 1);

    int ans = 0;

    for (int i = 1; i <= n; i ++ ) {
        fin >> geust[i];
        T.add(L[geust[i]], 1);
        g[geust[i]].push_back(i);
        int a = T.query(L[geust[i]] - 1), b = T.query(R[geust[i]] + 1, n);
        if (a > b) {
            ans += b;
            res[i] = 1;
            tab[geust[i]].push_back(i);
        } else {
            ans += a;
            res[i] = 0;
            tab[geust[i]].push_front(i);
            cout << tab[geust[i]].front() << endl;
        }
    }
    
    cout << ans << endl;

    for (int i = 1; i <= n; i ++ ) {
        int idx = 0;
        for (auto j : tab[i]) {
            res[j] = idx + L[i];
            idx ++ ;
        }
    }

    for (int i = 1; i <= n; i ++ ) {
        cout << res[i] << " ";
    }
}