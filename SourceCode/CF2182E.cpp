/*
    @ Author:       Eric / Sky__White
    @ Filename:     CF2182E.cpp
    @ Date:         12/07/2026
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

void solve() {
    int n, m, k; fin >> n >> m >> k;

    vector<int> arr(m + 1);

    for (int i = 1; i <= m; i ++ )
        fin >> arr[i];

    struct Node {
        int x, y, z;
    }; vector<Node> fri(n + 1);

    for (int i = 1; i <= n; i ++ ) {
        fin >> fri[i].x >> fri[i].y >> fri[i].z;
        k -= fri[i].y;
    }

    sort(1 + all(arr));

    priority_queue<int> q;

    sort(1 + all(fri), [&](Node a, Node b) {
        return a.x < b.x;
    });

    int opt = 1, res = 0;

    for (int i = 1; i <= m; i ++ ) {
        while (opt <= n and fri[opt].x <= arr[i])
            q.push(fri[opt].z - fri[opt].y), opt ++ ;
        if (q.size())
            q.pop(), res ++ ;
        // cout << i << " " << q.size() << endl;
    }
    while(opt <= n) {
        q.push(fri[opt].z - fri[opt].y), opt ++ ;
    }

    priority_queue<int, vector<int>, greater<int> > q2;
    
    while(q.size()) {
        q2.push(q.top()), q.pop();
    }

    while(q2.size()) {
        // cout << k << " ";
        k -= q2.top();
        // cout << k << endl;
        if (k < 0) break;
        res ++ ; q2.pop();
    }

    cout << res << endl;
}

signed main() {
    int T; fin >> T;

    while(T -- ) {
        solve();
    }
}