/*
    @ Author:       Eric / Sky__White
    @ Filename:     魔理沙偷走了重要的东西.cpp
    @ Date:         28/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <vector>
#include <queue>

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

const int Mod = 1e9;

signed main() {
    // freopen("steal.in", "r", stdin);
    // freopen("steal.out", "w", stdout);

    int n, q; fin >> n >> q;

    vector<int> b(n + 1);

    for (int i = 1; i <= n; i ++ )
        fin >> b[i];

    while(q -- ) {
        int m, k, x, y; fin >> m >> k >> x >> y;

        if (k == 1) {
            cout << 0 << endl;
            continue;
        }

        vector<int> s;

        for (int i = 1; i <= n; i ++ ) {
            int cur = (b[i] * x + y) % Mod + 1;
            s.push_back(cur);
        }

        sort(all(s)); reverse(all(s));
        queue<int> q;

        int sum = 0;
        int cnt = 0;

        for (int i = 0; i < min(m, (int)s.size()) and cnt < m; ) {
            if (q.empty() or s[i] > q.front()) {
                q.push(s[i] / k);
                sum += s[i] - s[i] / k;
                i ++ ;
            } else {
                q.push(q.front() / k);
                sum += q.front() - q.front() / k;
                q.push(q.front() - q.front() / k);
                q.pop();
            }
            cnt ++ ;
        }

        while(cnt < m) {
            if (q.front() == 0) break;
            q.push(q.front() / k);
            sum += q.front() - q.front() / k;
            q.pop();
            cnt ++ ;
        }

        cout << sum << endl;
    }
}