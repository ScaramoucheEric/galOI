/*
    @ Author:       Eric / Sky__White
    @ Filename:     P2107.cpp
    @ Date:         10/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
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
            x = sum * opt;
            return *this;
        }
    };
}
#define int long long
#define all(a) a.begin(), a.end()

using namespace std; Read fin;

signed main() {
    int n, m; cin >> n >> m;

    vector<pair<int, int> > arr(n + 1);

    for (int i = 1; i <= n; i ++ ) {
        fin >> arr[i].first >> arr[i].second;
    }

    sort(1 + all(arr));

    int dis = 0, sum = 0, res = 0, ans = 0;
    priority_queue<int> q;

    for (int i = 1; i <= n; i ++ ) {
        dis = arr[i].first; sum += arr[i].second; ans ++ ;
        q.push(arr[i].second);

        while (q.size() and sum + dis > m) {
            sum -= q.top(); q.pop();
            ans -- ;
        }

        cout << ans << endl;
        
        res = max(res, ans); 
    }

    cout << res << endl;
}