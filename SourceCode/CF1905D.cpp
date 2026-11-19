/*
    @ Author:       Eric / Sky__White
    @ Filename:     CF1905D.cpp
    @ Date:         05/24/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <functional>
#include <queue>
#include <set>
#include <deque>

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

signed main() {
    int t; fin >> t;
    while (t--) {
        int n; fin >> n;
        vector<int> p(n + 1);
        for (int i = 1; i <= n; i ++ ) fin >> p[i];

        deque<pair<int, int> > dq;
        vector<int> cnt(n + 1, 0);
        int mex = 0;
        int sum = 0;
        for (int i = 1; i <= n; i ++ ) {
            cnt[p[i]]++;
            while (cnt[mex]) mex++;
            dq.push_back({mex, 1});
            sum += mex; 
        }
 
        int ans = sum;
        for (int i = 1; i < n; i ++ ) {
            sum -= dq.front().first;
            dq.front().second--;
            // cout << dq.front().second << endl;
            if (dq.front().second == 0) dq.pop_front();

            pair<int, int> cur = {p[i], 0};
            while (!dq.empty() && dq.back().first > p[i]) {
                sum -= dq.back().first * dq.back().second;
                cur.second += dq.back().second;
                dq.pop_back();
            }

            dq.push_back(cur);
            sum += cur.first * cur.second;

            dq.push_back({n, 1}); 
            sum += n;

            ans = max(ans, sum);
        }

        cout << ans << endl;
    }
    return 0;
}