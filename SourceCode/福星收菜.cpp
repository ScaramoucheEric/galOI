/*
    @ Author:       Eric / Sky__White
    @ Filename:     福星收菜.cpp
    @ Date:         21/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

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
typedef pair<int, int> PII;
const int INF = 0x3f3f3f3f3f3f3f3f;

signed main() {
    // freopen("fuxing.in", "r", stdin);
    // freopen("fuxing.out", "w", stdout);
    
    int n, m; fin >> n >> m;
    vector<int> k(n + 1), p(n + 1);
    for (int i = 1; i <= n; i ++ )
        fin >> k[i] >> p[i];

    vector<int> x(n + 1);
    for (int i = 1; i <= n; i ++ ) fin >> x[i];

    unordered_map<int, int> sum_k;
    int max_p = 0;
    vector<int> y(n + 2, 0);
    int res = 0;
    for (int i = 1; i <= n; i ++ ) {
        sum_k[k[i]] += p[i];
        max_p = max(max_p, p[i]);
        int op1 = sum_k[x[i]];
        int op2 = max_p;
        y[i] = max(op1, op2);
        res += y[i];
    }

    int len = n - 1;
    vector<int> v(len + 5, 0);
    for (int i = 1; i <= len; i ++ ) {
        v[i] = y[i + 1] - y[i];
    }

    vector<int> L(len + 5), R(len + 5);
    vector<bool> del(len + 5, false);
    priority_queue<PII> q;

    for (int i = 1; i <= len; i ++ ) {
        L[i] = i - 1;
        R[i] = i + 1;
        q.emplace(v[i], i);
    }
    R[0] = 1; L[len + 1] = len;

    int ans = 0, cnt = 0;
    while (!q.empty() && cnt < m) {
        auto [val, id] = q.top(); q.pop();
        if (del[id] || val <= 0) continue;

        ans += val;
        cnt ++ ;

        int l = L[id], r = R[id];

        int new_val = v[l] + v[r] - v[id];
        v[id] = new_val;

        del[l] = del[r] = true;

        L[id] = L[l]; R[id] = R[r];
        R[L[id]] = id; L[R[id]] = id;

        q.emplace(new_val, id);
    }

    cout << res + ans << '\n';
    return 0;
}